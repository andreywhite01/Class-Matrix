#include "testing.h"


void Test() {
	{
		Matrix m1;
		double* row1 = new double[3]{ 1,2,3 };
		double* row2 = new double[3]{ 4,5,6 };
		double* row3 = new double[3]{ 7,8,9 };
		double** rows = new double* [3]{ row1,row2,row3 };
		m1.SetValues(rows, 3, 3);

		Matrix m2;
		row1 = new double[3]{ 9,8,7 };
		row2 = new double[3]{ 6,5,4 };
		row3 = new double[3]{ 3,2,1 };
		rows = new double* [3]{ row1,row2,row3 };
		m2.SetValues(rows, 3, 3);
		
		Matrix sum;
		row1 = new double[3]{ 10,10,10 };
		row2 = new double[3]{ 10,10,10 };
		row3 = new double[3]{ 10,10,10 };
		rows = new double* [3]{ row1,row2,row3 };
		sum.SetValues(rows, 3, 3);

		Matrix dif;
		row1 = new double[3]{ -8,-6,-4 };
		row2 = new double[3]{ -2,0,2 };
		row3 = new double[3]{ 4,6,8 };
		rows = new double* [3]{ row1,row2,row3 };
		dif.SetValues(rows, 3, 3);

		Matrix mult;
		row1 = new double[3]{ 30, 24, 18 };
		row2 = new double[3]{ 84, 69, 54 };
		row3 = new double[3]{ 138, 114, 90 };
		rows = new double* [3]{ row1,row2,row3 };
		mult.SetValues(rows, 3, 3);

		Matrix transposed;
		row1 = new double[3]{ 1, 4, 7 };
		row2 = new double[3]{ 2, 5, 8 };
		row3 = new double[3]{ 3, 6, 9 };
		rows = new double* [3]{ row1,row2,row3 };
		transposed.SetValues(rows, 3, 3);

		Assert(m1 + m2, sum, "1");
		Assert(m1 - m2, dif, "2");
		Assert(m1 * m2, mult, "3");
		Assert(!m1, transposed, "4");
		Assert(m1 + m2 - m1, m2, "5");
		Assert(m1 += m2, sum, "6");

		delete[] row1;
		delete[] row2;
		delete[] row3;
		delete[] rows;
	}
}