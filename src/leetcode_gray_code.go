// https://leetcode.com/problems/gray-code/
package main

import("fmt")

    func grayCode(n int)[] int {
        var result []int

	for i := 0;
        i < (1 << n);
        i++ { result = append(result, i ^ (i >> 1)) }

        return result
}

func main() {
tests:= []int{
        1, 2}

	for _, t := range tests {
        fmt.Println(grayCode(t))
    }
}
