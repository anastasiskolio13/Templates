#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

template<typename T>
class MergeSortTree
{
private:
	struct Node
	{
		/// <summary>
		/// The sorted vector of the current node.
		/// </summary>
		std::vector<T> A;

		/// <summary>
		/// The left child of the current node.
		/// </summary>
		Node* left;

		/// <summary>
		/// The right child of the current node.
		/// </summary>
		Node* right;
	};

	/// <summary>
	/// The root of the Merge Sort Tree.
	/// </summary>
	Node* root;

	/// <summary>
	/// The number of elements in the input array.
	/// </summary>
	const int N;

	/// <summary>
	/// Recursively constructs the Merge Sort Tree. 
	/// </summary>
	/// <param name="A">The vector that the tree will be built on.</param>
	/// <param name="current">Current node of the tree.</param>
	/// <param name="lo">First index of the segment that this node contains.</param>
	/// <param name="hi">Last index of the segment that this node contains.</param>
	void ConstructTree(const std::vector<T>& A, Node*& current, int lo, int hi)
	{	
		// If the current node is null, create a new node.
		if (current == nullptr)
		{
			current = new Node();
		}

		// If the current segment has only one element, assign that element to the current node and return.
		if (lo == hi)
		{
			current->A = { A[lo] };
			return;
		}

		// Otherwise, split the current segment into two halves.
		int mid = (lo + hi) / 2;

		// Recursively construct the left subtree.
		ConstructTree(A, current->left, lo, mid);

		// Recursively construct the right subtree.
		ConstructTree(A, current->right, mid + 1, hi);

		// Merge the sorted vectors from the left and right subtrees into the current node's vector.
		std::merge(current->left->A.begin(), current->left->A.end(), current->right->A.begin(), current->right->A.end(), std::back_inserter(current->A));
	}

	int Count(const T k, const int qlo, const int qhi, Node* current, int lo, int hi, std::function<int(const std::vector<T>&, const T)> count) const
	{
		// If the current node is null, no elements exist in the current node, so return 0.
		if (current == nullptr)
		{
			return 0;
		}

		// If the current segment is completely outside the query range, return 0.
		if (qlo > hi || qhi < lo)
		{
			return 0;
		}

		if (qlo <= lo && hi <= qhi)
		{
			return count(current->A, k);
			//return current->A.size() - (std::upper_bound(current->A.begin(), current->A.end(), k) - current->A.begin());
		}

		// Otherwise, split the current segment into two halves.
		int mid = (lo + hi) / 2;

		int countLeft = Count(k, qlo, qhi, current->left, lo, mid, count);

		int countRight = Count(k, qlo, qhi, current->right, mid + 1, hi, count);

		return countLeft + countRight;
	}

public:
	/// <summary>
	/// Initializes the root of the tree and the number of elements in the input array, then constructs the Merge Sort Tree.
	/// </summary>
	/// <param name="A">The vector that the tree will be built on.</param>
	MergeSortTree(const std::vector<T>& A) : root(new Node()), N(A.size())
	{
		ConstructTree(A, root, 0, N - 1);
	}

	/// <summary>
	///
	/// </summary>
	/// <param name="k">The element whose number of larger elements is being computed.</param>
	/// <param name="qlo">First index of the query range.</param>
	/// <param name="qhi">Last index of the query range.</param>
	/// <returns>The number of elements greater than k in the segment [qlo, qhi].</returns>
	int FindNumberOfGreaterElements(const T k, const int qlo, const int qhi) const
	{
		return Count(k, qlo, qhi, root, 0, N - 1, [](const std::vector<T>& A, const T k) { return A.end() - std::upper_bound(A.begin(), A.end(), k); });
	}
};

