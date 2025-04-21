// https://leetcode.com/problems/stone-game/
// Alex always wins because
// - the total number of stones in the pile are odd
// - the length of array is even
// - alex can take all the even numbered or odd numbered stones

package main

import("fmt")

    func main() {
tests:
    = [] int { 4, 3, 2, 3 }

      if stoneGame (tests) == true {
        fmt.Println("ok")
    }
}

func stoneGame(piles[] int) bool { return true }
