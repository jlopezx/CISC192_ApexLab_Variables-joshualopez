#include <iostream>
#include <sstream>
#include <iomanip>
#include "apex_code.h"
/* File: apex_code.cpp
 * Class: CISC 192 - C++
 * Professor: Chow
 * Written by: Joshua Lopez
 * Description: The code here is called by testbench.cpp and tests minutes_to_12hour_time() and
 *    numbers_to_12hour_time() functions.
 *  -minutes_to_12hour_time() takes a stream of inputted numbers, and converts them to
 *     hours:minutes in a 12-hour:60 minute format.
 *  -numbers_to_12hour_time() also takes a stream of inputted numbers but in the form of
 *    raw hours, raw minutes, and raw seconds and converts them to a 12-clock system format with the
 *    hour being with 0-11, and minutes and seconds being within 0-59 in the following order and
 *    format: "<hours>:<minutes>.<seconds> !" */
using namespace std;

// Declared these double variables to hold the inputs from the caller (testbench.cpp in this case)
double inputSeconds;
double inputMinutes;
double inputHours;

// Constants declared for time conversion and clock cycle as they are often used for conversion and modulo
const int TIME_CONVERSION = 60;
const int CLOCK_CYCLE = 12;

void minutes_to_12hour_time(stringstream &cin, stringstream &cout) {
    // Place code for translating minutes to 12 hour time
    // Pretend this is your main function and you can use cin/cout
    // as you would in main.

    // If you want to print to the console for debugging use std::cout.
    // Use cout for your final solution.

    // First you want to get user input with cin
    // Do any needed calculations
    // Create output with cout

	// Used to hold simple time converstions and for outputs
	int outputMinutes;
	int outputHours;

	// Passes in the system inputs into inputMinutes
	cin >> inputMinutes;

	// -static casts are used because we're using modulo operations
	// -Manipulates inputMinutes by getting the remainder through modulo 60
	outputMinutes = static_cast<int>(inputMinutes) % TIME_CONVERSION;
	// -Subtracts the remainder minutes from what can be converted into perfect hours.
	outputHours = (static_cast<int>(inputMinutes - outputMinutes) / TIME_CONVERSION) % CLOCK_CYCLE;
	// -Outputs hours and minutes in a 12 hour : 60 minute format
	cout << outputHours << ":" << outputMinutes << " !";
}

void numbers_to_12hour_time(stringstream& cin, stringstream& cout) {
    // Place code for translating hours, minutes and seconds to 12 hour time
    // Pretend this is your main function and you can use cin/cout
    // as you would in main.

    // If you want to print to the console for debugging use std::cout.
    // Use cout for your final solution.

	/* -Double is used for all these variables as majority of the values involve floating-point values
	 * -My clock variables used for outputs. Easier to read and understand code with these. */
	double clockOutputSecs;
	double clockOutputMins;
	double clockOutputHours;
	/* -Remainder variables are going to hold remainder values which will be applied with a modulo of
	 *   TIME_CONVERSION (60) to get what would be left over after converting minutes and seconds*/
	double minutesRemainder;
	double secsRemainder;
	/* -The next two variables are used for converting hours to minutes and seconds since inputHours
	 *   can have a decimal point value. */
	double hourToMin;
	double minToSec;
	// -These variables will hold the converted minutes and seconds to hours
	double minToHours;
	double secToHours;
	// -This variable would be used to hold the converted value from seconds to minutes
	double secToMin;
	// -Total variables simply hold their respective total values after calculations.
	double totalMinutes;
	double totalHours;
	double totalSeconds;

	// -Takes in the inputs from testbench.cpp.
	cin >> inputHours;
	cin >> inputMinutes;
	cin >> inputSeconds;

	/* -This takes the decimal from inputHours and converts it to minutes and seconds used later to add
	 *   to the totals.
	 * -Int static casts are used to remove the decimal point from inputHours and subtract it by
	 *   inputHours so ONLY the decimal is left behind. This is multiplied by 60 to get a minutes conversion.
	 * -minToSec's calculation also uses a static_cast<int> because a particular value can have a
	 *   decimal value carried from the hours to minutes conversion. */
	hourToMin = (inputHours - static_cast<int>(inputHours)) * TIME_CONVERSION;
	minToSec = (hourToMin - static_cast<int>(hourToMin)) * TIME_CONVERSION;

	/* -secsRemainder takes inputSeconds and applys a modulo operation of 60 to get the remainder of the
	 *   seconds that would be left over after the conversion to minutes
	 * -minutesRemainder takes inputMinutes and applys a modulo operation of 60 to get the remainder of the
	 *   minutes that would be left over after conversion to hours
	 * -static_cast<int> is applied to both since modulo operation only works with int values here*/
	secsRemainder = static_cast<int>(inputSeconds) % TIME_CONVERSION;
	minutesRemainder = static_cast<int>(inputMinutes) % TIME_CONVERSION;

	/* -totalSeconds adds the seconds from hours's decimal value if applicable, and what is remaining
	 *   in seconds after it has been converted into minutes. */
	totalSeconds = minToSec + secsRemainder;

	/* -Converts inputted seconds into minutes.
	 * -It subtracts by secsRemainder to get a cleaner result. */
	secToMin = (inputSeconds - secsRemainder) / TIME_CONVERSION;

	/* -totalMinutes is comprised from 3 sections. The decimal value in hours, the remainder in minutes
	 *   meaning anything not converted into hours, and the overflow from seconds. */
	totalMinutes = hourToMin + minutesRemainder + secToMin;

	/* -secToHours converts the seconds from the input into hours by dividing them by 3600 since that
	 *   value in seconds equals 1 hour
	 * -minToHours converts the minutes from the input into hours by divinding them by 60 since that
	 *   value in minutes equals 1 hour. */
	secToHours = inputSeconds / (TIME_CONVERSION*TIME_CONVERSION);
	minToHours = inputMinutes / TIME_CONVERSION;

	/* -totalHours adds the hours from the input minus the decimal and the hours in minutes
	 *   Need a static cast here to remove the decimal from hours as it's a significant value for minutes
	 *   and seconds Keep in mind that totalMinutes also gets the minutes from seconds which could be
	 *   significant and contribute to hours. */
	totalHours = static_cast<int>(inputHours) + minToHours + secToHours;

	/* -clockOutputHours takes the total hours calculated and does a modulo of 12 to keep align with the
	 *   12-hour clock cycle
	 * -clockOutputMins takes the total minutes calculated and does a modulo of 60 to keep align with the
	 *   60 second cycle format *
	 * -clockOutputSecs takes the toal seconds calculated. Modulo isn't necessary as it was done before or
	 *   already within the parameters of a 60 second cycle format*/
	clockOutputHours = static_cast<int>(totalHours) % CLOCK_CYCLE;
	clockOutputMins = static_cast<int>(totalMinutes) % TIME_CONVERSION;
	clockOutputSecs =  totalSeconds;

	/* -Output that is tested against in testbench.
	 * -Avoid endl as it will fail all the tests.
	 * -clockOutputSecs needs setprecision(2) set due to test 16 being a special case involving the
	 *   decimal number being carried from hours to minutes and to seconds */
	cout << clockOutputHours << ":" << clockOutputMins << "." << setprecision(2) << clockOutputSecs << " !";

}
