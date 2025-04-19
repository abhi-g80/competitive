// https://open.kattis.com/problems/stockprices
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int testcases, n;
    string order_type, s, t;

    cin >> testcases;

    while (testcases--) {
        cin >> n;

        vector<int> bid(1001, 0);
        vector<int> ask(1001, 0);
        int best_bid = 0, best_ask = 0, qty, prc;
        string s, t, order_type;

        while (n--) {
            cin >> order_type >> qty >> s >> t >> prc;
            if (order_type == "buy") {
                bid[prc] += qty;
                if (best_bid < prc) best_bid = prc;
            }
            if (order_type == "sell") {
                ask[prc] += qty;
                if (best_ask > prc) best_ask = prc;
            }
            if (best_bid == 0 && order_type == "buy") {
                best_bid = prc;
            }
            if (best_ask == 0 && order_type == "sell") {
                best_ask = prc;
            }
            int t_prc = 0;
            if (best_bid >= best_ask) {
                // trade
                if (order_type == "buy") {
                    for (int i = best_ask; i < ask.size(); i++) {
                        if (ask[i] == 0) continue;  // no order at this price
                        if (prc >= i && qty > 0) {
                            int tq = max(qty, ask[i]);
                            ask[i] -= tq;
                            bid[prc] -= tq;
                            qty -= tq;
                            t_prc = i;
                            continue;
                        } else {
                            best_ask = i;
                            break;
                        }
                    }
                    if (qty > 0) {
                        best_bid = prc;
                    }
                }
                if (order_type == "sell") {
                    for (int i = best_bid; i < bid.size(); i++) {
                        if (bid[i] == 0) continue;  // no order at this price
                        if (prc >= i && qty > 0) {
                            int tq = max(qty, bid[i]);
                            bid[i] -= tq;
                            ask[prc] -= tq;
                            qty -= tq;
                            t_prc = i;
                            continue;
                        } else {
                            best_bid = i;
                            break;
                        }
                    }
                    if (qty > 0) {
                        best_ask = prc;
                    }
                }
            }
            cout << "best ask: " << best_ask << " best bid: " << best_bid << " trade prc: " << t_prc
                 << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
