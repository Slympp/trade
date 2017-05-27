#ifndef 	__TRADE__HPP__
# define 	__TRADE__HPP__

# include 	<iostream>
# include 	<string>
# include 	<vector>
# include 	<stdlib.h>
# include 	<math.h>

using namespace std;

# define 		PERCENT_RANGE	10
# define 		PERCENT_SELL	30
# define 		PERCENT_BUY		10

class 			Trade {

public:
	Trade();
	~Trade();
	
	bool 			is_valid_period(void);
	void 			read(void);
	void 			run(void);

	vector<float> 	rate;

private:
	// Data manipulations
	float 			getCom(void);
	int				getDailyPrice(void);
	int 			getAverage(void);
	int 			getAllowedBuy(void);
	int 			getAllowedSell(void);

	// Algorithm
	void 			beforeLastDay(void);


	// Basics
	void 			sell(int);
	void 			buy(int);
	void 			wait(void);

	int 			money;
	int 			shares;
	int 			dayTotal;
	int				dayCurrent;
};	

#endif