#include <iostream>
#include <mutex>
#include <vector>

#include "OffsetPtr.hpp"

struct Node {
	int data;
	OffsetPtr<Node> next;
};

int main()
{
	const int numNodes = 5;
	Node nodes[numNodes];

	for (int i = 0; i < numNodes - 1; ++i) {
		nodes[i].data = i;
		nodes[i].next.set(nodes, &nodes[i + 1]);
	}
	nodes[numNodes - 1].data = numNodes - 1;
	nodes[numNodes - 1].next.set(nodes, nullptr);

	//create a vector of OffsetPtr<Node>
	std::vector<OffsetPtr<Node>>ptrs;
	ptrs.reserve(numNodes);
	for (int i = 0; i < numNodes; ++i) {
		ptrs.emplace_back(OffsetPtr<Node>(nodes, &nodes[i]));
	}

	for (const auto& ptr : ptrs) {
		Node* node = ptr.get(nodes);
		if (node)
			std::cout << "Node data: " << node->data << std::endl;
	}

	return 0;
}