#include "PmergeMe.hpp"

#include <cstddef>
#include <stdexcept>

namespace
{
	struct Node
	{
		unsigned int value;
	};

	struct Pending
	{
		std::size_t loser;
		std::size_t winner;

		Pending(std::size_t loserIndex, std::size_t winnerIndex)
			: loser(loserIndex), winner(winnerIndex)
		{
		}
	};

	template <typename Container>
	std::size_t findPending(const Container &pending, std::size_t winner)
	{
		for (std::size_t i = 0; i < pending.size(); ++i)
		{
			if (pending[i].winner == winner)
				return i;
		}
		throw std::logic_error("missing Ford-Johnson pair");
	}

	template <typename Container>
	std::size_t findPosition(const Container &values, std::size_t value)
	{
		for (std::size_t i = 0; i < values.size(); ++i)
		{
			if (values[i] == value)
				return i;
		}
		throw std::logic_error("missing Ford-Johnson winner");
	}

	template <typename Sequence, typename NodeContainer>
	void insertValue(Sequence &chain, std::size_t value,
		const NodeContainer &nodes, std::size_t bound)
	{
		std::size_t first = 0;
		std::size_t last = bound;
		while (first < last)
		{
			std::size_t middle = first + (last - first) / 2;
			if (nodes[chain[middle]].value < nodes[value].value)
				first = middle + 1;
			else
				last = middle;
		}
		chain.insert(chain.begin() + first, value);
	}

	template <typename Sequence, typename PendingContainer, typename NodeContainer>
	void insertPairLoser(Sequence &chain, const Sequence &winners,
		const PendingContainer &pending, const NodeContainer &nodes,
		std::size_t winnerPosition)
	{
		std::size_t pendingPosition = findPending(pending, winners[winnerPosition]);
		std::size_t bound = findPosition(chain, winners[winnerPosition]);
		insertValue(chain, pending[pendingPosition].loser, nodes, bound);
	}

	template <typename Sequence, typename PendingContainer, typename NodeContainer>
	void fordJohnson(Sequence &values, const NodeContainer &nodes,
		const PendingContainer &pendingType)
	{
		if (values.size() < 2)
			return;

		Sequence winners;
		PendingContainer pending;
		std::size_t i = 0;
		for (; i + 1 < values.size(); i += 2)
		{
			std::size_t first = values[i];
			std::size_t second = values[i + 1];
			std::size_t winner = first;
			std::size_t loser = second;
			if (nodes[first].value < nodes[second].value)
			{
				winner = second;
				loser = first;
			}
			winners.push_back(winner);
			pending.push_back(Pending(loser, winner));
		}
		const bool hasOddValue = i < values.size();
		const std::size_t oddValue = hasOddValue ? values[i] : 0;

		fordJohnson(winners, nodes, pendingType);

		Sequence chain;
		std::size_t firstPair = findPending(pending, winners[0]);
		chain.push_back(pending[firstPair].loser);
		for (std::size_t winnerIndex = 0; winnerIndex < winners.size(); ++winnerIndex)
			chain.push_back(winners[winnerIndex]);

		const std::size_t pairCount = pending.size();
		const std::size_t pendingCount = pairCount + (hasOddValue ? 1 : 0);
		std::size_t older = 1;
		std::size_t current = 3;
		while (older < pendingCount)
		{
			std::size_t blockEnd = current < pendingCount ? current : pendingCount;
			for (std::size_t index = blockEnd; index > older; --index)
			{
				if (index <= pairCount)
					insertPairLoser(chain, winners, pending, nodes, index - 1);
				else if (hasOddValue)
					insertValue(chain, oddValue, nodes, chain.size());
			}
			std::size_t next = current + 2 * older;
			older = current;
			current = next;
		}
		values = chain;
	}
}

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &)
{
	return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::sortVector(std::vector<unsigned int> &values) const
{
	std::vector<Node> nodes;
	std::vector<std::size_t> indices;
	std::vector<Pending> pendingType;
	for (std::size_t i = 0; i < values.size(); ++i)
	{
		Node node = {values[i]};
		nodes.push_back(node);
		indices.push_back(i);
	}
	fordJohnson(indices, nodes, pendingType);
	for (std::size_t i = 0; i < values.size(); ++i)
		values[i] = nodes[indices[i]].value;
}

void PmergeMe::sortDeque(std::deque<unsigned int> &values) const
{
	std::deque<Node> nodes;
	std::deque<std::size_t> indices;
	std::deque<Pending> pendingType;
	for (std::size_t i = 0; i < values.size(); ++i)
	{
		Node node = {values[i]};
		nodes.push_back(node);
		indices.push_back(i);
	}
	fordJohnson(indices, nodes, pendingType);
	for (std::size_t i = 0; i < values.size(); ++i)
		values[i] = nodes[indices[i]].value;
}
