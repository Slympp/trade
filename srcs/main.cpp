#include "Trade.hpp"

int			main() {
	Trade	trade;
	string 	s;

	trade.read();

	cin >> s;
	trade.rate.push_back(atoi(s.c_str()));
	while (trade.is_valid_period() && s != "--end--" && s != "--END--") {
		trade.run();
		s = "";
		cin >> s;
		trade.rate.push_back(atoi(s.c_str()));
	}
	return (0);
}