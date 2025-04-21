# https:  // leetcode.com/problems/subsets-ii/
from typing import List, Tuple


class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[Tuple[int]]:
        n = len(nums)
        result = set()
        nums.sort()
        for i in range(2**n):
            ans = []
            for j in range(n):
                if i & (1 << j):
                    ans.append(nums[j])
            result.add(tuple(ans))
        return list(result)


def check(solution, test: List[int], ans: List[Tuple[int]]) -> None:
    assert solution.subsetsWithDup(test) == [(), (2,)], "test failed :("


def main():
    solution = Solution()

    test = [2]
    ans = [(), (2,)]

    check(solution, test, ans)
    print("ok")


if __name__ == "__main__":
    main()
