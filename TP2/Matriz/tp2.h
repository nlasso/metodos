#ifndef TP2_H_
#define TP2_H_
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;


class PrattTruss{
	public:
		PrattTruss(int h, int span, int n);
	private:
		Matriz _matriz;
}