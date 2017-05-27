#include "Trade.hpp"

Trade::Trade() {
	this->money = 0;
	this->shares = 0;
	this->dayTotal = 0;
	this->dayCurrent = 0;
}
Trade::~Trade() { }

bool 	Trade::is_valid_period(void) {

	if (this->dayTotal < 1 || this->dayCurrent > this->dayTotal) 
		return (false);
	return (true);
}

void 		Trade::read(void) {
	cin >> this->money;
	cin >> this->dayTotal;
}

// Retourne le prix moyen du cours depuis le premier jour.
int 	Trade::getAverage(void) {
	int avg = 0, i = 0;

	while (rate[i])
		avg += rate[i++];
	return (avg /= i);
}

// Combien peut-on se permettre d'acheter, selon PERCENT_BUY
int 	Trade::getAllowedBuy(void) {
	int nb;

	nb = (this->money / getDailyPrice()) - 1;
	nb = nb / 100 * PERCENT_BUY;
	cerr << " - Allowedbuy: " << nb;
	if (nb == 0)
		nb = 1;
	return (nb);
}

// Combien peut-on se permettre de vendre, selon PERCENT_SELL
int 	Trade::getAllowedSell(void) {
	int nb;

	nb = shares;
	nb = nb / 100 * PERCENT_SELL;
	cerr << " - Allowedsell: " << nb;
	if (nb == 0)
		nb = 1;
	return (nb);
}

// On vend tout ce qu'il reste l'avant-dernier jour
void 	Trade::beforeLastDay(void) { 

	if (shares > 0)
		sell(shares);
	else
		wait();		
}

void 	Trade::run(void) {

	cerr << dayCurrent
	<< "\t> Avg: " << getAverage()
	<< " - Money: " << money
	<< " - Shares: " << shares
	<< " - Daily: " << getDailyPrice()
	<< " - Avg-: " << getAverage() - (getAverage() / PERCENT_RANGE)
	<< " - Avg+: " << getAverage() + (getAverage() / PERCENT_RANGE);
	

	// tant qu'on n'est pas le dernier jour
	if (this->dayCurrent != this->dayTotal) {

		// on vend tout ce qu'il reste l'avant-dernier jour pour maximiser le profit
		if (this->dayTotal - 1 == this->dayCurrent)
			beforeLastDay();
		else {

			// Algorithme simpliste : on compare le prix du jour avec la moyenne du cours.
			// Si le prix du jour est avantageux à l'achat/vente, on agit en conséquence,
			// sinon on attend.

			if (this->dayCurrent == 0) {
				buy(getAllowedBuy());
			} else if (getDailyPrice() <= getAverage() - (getAverage() / PERCENT_RANGE))
				buy(getAllowedBuy());
			else if (getDailyPrice() >= getAverage() + (getAverage() / PERCENT_RANGE))
				sell(getAllowedSell());
			else
				wait();

		}
	} else
		wait();

	this->dayCurrent++;
}

float 	Trade::getCom() { return (this->money * 0.15 /100); }
int		Trade::getDailyPrice(void) { return (rate[this->dayCurrent]); }

// Vend NB actions et soustrait la commission de 0.15%
void 	Trade::sell(int nb) {

	if (nb <= this->shares && nb > 0) {
		cerr << "SELL " << nb << endl;
		cout << "sell " << nb << endl;
		this->shares -= nb;
		this->money += ceil((nb * getDailyPrice()) - getCom());
	} else
		wait();
}

// Achète NB actions et soustrait la commission de 0.15%
void 	Trade::buy(int nb) {

	if (ceil((nb * getDailyPrice()) + getCom()) < this->money && nb > 0) {
		cerr << "BUY " << nb << endl;
		cout << "buy " << nb << endl;
		this->shares += nb;
		this->money -= ceil((nb * getDailyPrice()) + getCom());
	} else 
		wait();
}

void 	Trade::wait(void) {
	cerr << endl;
	cout << "wait" << endl;
}