#include <string.h>
#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <menuFtype.h>
#include <errlog.h>
#include <epicsString.h>
#include <epicsExport.h>
#include <math.h>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "keyence.h"

std::vector<std::string> parseInput(const std::string& input)
{
/**
 * Chops the output string up into a vector containing the output from only one channel
 * Input: input, the raw string from the device
 * Output: channelwise_output, a vector of strings containing the individual outputs from each channel
**/

    // 9 characters includes the 7 digit characters, (+/-), and a leading comma for each channel
    const int channel_string_length = 9;
    std::vector<std::string> channelwise_output;

    unsigned int numberOfChannels = floor(input.length()/channel_string_length);

    // This assumes that the length of the array will be exactly as long as the number of outputs we have, which is not going to be the case?
    for(unsigned int i=0;i<numberOfChannels;i++)
    {
        try {
            channelwise_output.push_back (input.substr((i*channel_string_length)+1, channel_string_length-1));
        } catch (std::out_of_range) {
            puts("Caught out of range error, device output string too short?");
        }
    }

	return channelwise_output;
}

std::string get_str_from_epics(char* raw_rec, long stringLength)
{
/**
 * Builds up a std::string given an input char* from EPICS record
 * Inputs: char* raw_rec, the raw string from the epics record
 *         long stringLength, the number of characters in the string (from NORD waveform field)
 *
 * Output: str, the std::string representation of raw_rec
 */

    std::string str;

    for (int i = 0; i < stringLength; i++) {

            str.push_back(raw_rec[i]);
    }

    return str;
}

double get_channel_value(const std::string& channel_string)
{
/**
 * Converts each string segment to Float.
 * A string of (+/-)FFFFFFF denotes an out of range measurment. NaN is returned in this case.
 * A string of XXXXXXXX denotes an output which is turned off. NaN is returned in this case.
 *
 * Input: std::string channel_string, The string output of the channel
 * Output: float, The value contained within the channel string or NaN.
 */

    if (std::string::npos != channel_string.find("+F")) {
        return INFINITY;

    } else if (std::string::npos != channel_string.find("-F")) {
        return -INFINITY;

    } else if (std::string::npos != channel_string.find("X")){
        return NAN;

    } else {
	    return std::stof (channel_string);
	}
}

long keyence_status_parse_impl(aSubRecord* prec)
/**
 * Parses an aSubRecord from EPICS containing the string output from a Keyence TM3001P
 *
 * Input: aSubRecord* prec, the input aSub record containing the data to parse
 * Outputs: prec->vala through ->valp, the float values from the string
 */

{
    try {
    std::vector<std::string> split_strings;

    long inputLength = *(long*)prec->b;

    // This length comes from 16 channels, 9 characters per channel
    if (inputLength == 16*9) {

        split_strings = parseInput(get_str_from_epics((char*)prec->a, inputLength));

        *(double*)prec->vala = get_channel_value(split_strings[0]);
        *(double*)prec->valb = get_channel_value(split_strings[1]);
        *(double*)prec->valc = get_channel_value(split_strings[2]);
        *(double*)prec->vald = get_channel_value(split_strings[3]);
        *(double*)prec->vale = get_channel_value(split_strings[4]);
        *(double*)prec->valf = get_channel_value(split_strings[5]);
        *(double*)prec->valg = get_channel_value(split_strings[6]);
        *(double*)prec->valh = get_channel_value(split_strings[7]);
        *(double*)prec->vali = get_channel_value(split_strings[8]);
        *(double*)prec->valj = get_channel_value(split_strings[9]);
        *(double*)prec->valk = get_channel_value(split_strings[10]);
        *(double*)prec->vall = get_channel_value(split_strings[11]);
        *(double*)prec->valm = get_channel_value(split_strings[12]);
        *(double*)prec->valn = get_channel_value(split_strings[13]);
        *(double*)prec->valo = get_channel_value(split_strings[14]);
        *(double*)prec->valp = get_channel_value(split_strings[15]);

    } else {
        // String is of incorrect length
        return 1;
    }

    } catch (std::exception &e) {
        std::cout << e.what();

    } catch (...) {
        puts("Caught unknown exception");
    }

    return 0; /* process output links */
}
