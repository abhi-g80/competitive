# push dominoes
# https:  // leetcode.com/problems/push-dominoes/
#
# Analysis
# -- -- -- --
#
# case 1. L... L or R... R make all dots the same
# case 2. L... R don't do anything with dots
# case 3. R... L odd number of dots in between, leave middle one make left R and right L
# case 4. R....L even number of dots in between, half on left R and half on right L
# case 5. ..L or R..at the end, make all dots L or R respectively


class Solution:
    def push_dominoes(self, dominoes: str) -> str:
        dominoes = "L" + dominoes + "R"
        ans = ""
        lookback = 0

        for i in range(1, len(dominoes)):
            if dominoes[i] == ".":
                continue
            j = i - lookback - 1
            if lookback:
                ans += dominoes[lookback]
            if dominoes[lookback] == dominoes[i]:
                ans += dominoes[i] * j
            elif dominoes[lookback] == "L" and dominoes[i] == "R":
                ans += "." * j
            else:
                ans += "R" * (j // 2) + "." * (j % 2) + "L" * (j // 2)
            lookback = i
        return ans


def main():
    tests = ["RR.L.", "...L", "R..."]
    expected = ["RR.L.", "LLLL", "RRRR"]

    s = Solution()

    for i, t in enumerate(tests):
        ans = s.push_dominoes(t)
        assert ans == expected[i]

    print("ok")


if __name__ == "__main__":
    main()
