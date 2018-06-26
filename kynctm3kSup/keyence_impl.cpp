#include <string.h>
#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <menuFtype.h>
#include <errlog.h>
#include <epicsString.h>
#include <epicsExport.h>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

#include "keyence.h"

std::vector<std::string> parseInput(const std::string& input)
{
/**
 * Chops the output string up into a vector containing the output from only one channel
 * Input: input, the raw string from the device
 * Output: channelwise_output, a vector of strings containing the individual outputs from each channel
**/
    const int channel_string_length = 14;
    std::vector<std::string> channelwise_output;

    unsigned int numberOfChannels = floor(sizeof(input)/channel_string_length);

    std::cout << numberOfChannels << std::endl;

    // This assumes that the length of the array will be exactly as long as the number of outputs we have, which is not going to be the case?
    for(unsigned int i=0;i<numberOfChannels;i++)
    {
        std::cout << i << std::endl;
        try {
            channelwise_output.push_back (input.substr(i*channel_string_length, ((i+1)*channel_string_length)-1));
        } catch (std::out_of_range) {
            puts("Caught out of range error");
        }
    }

	return channelwise_output;
}

std::string get_str_from_epics(char* raw_rec, long stringLength)
{
    //char** rec = reinterpret_cast<char**>(raw_rec);
    std::string str;

    std::cout << "THE RAW STRING IS " << raw_rec << std::endl;

    for (int i = 0; i < stringLength; i++) {

            //std::cout << raw_rec[i] << std::endl;
            str.push_back(raw_rec[i]);
    }

    std::cout << "THE NEW STRING IS " << str << std::endl;

    return str;
}

float get_channel_value(const std::string& channel_string)
{
	return std::stof (channel_string.substr(6,13));
}

unsigned int get_channel_number(const std::string& channel_string)
{
	return std::stoi (channel_string.substr(3,4));
}


/**
 *  
 */
long keyence_status_parse_impl(aSubRecord* prec)
{
    try {
    std::vector<std::string> split_strings;

    long inputLength = 0;//*(long*)prec->b;

    std::cout << "\nString1 " << (char*)prec->a << std::endl;
    std::cout << "\nString Length " << *(long*)prec->b << std::endl;
    std::cout << "\nString Length " << inputLength << std::endl;


    if (inputLength > 0) {
    split_strings = parseInput(get_str_from_epics((char*)prec->a, inputLength));
    //split_strings = parseInput(get_str_from_epics((char*)prec->a, *(long*) prec->b));


    for (unsigned int i=0; i<split_strings.size(); i++)
    {
        std::cout << "\nRecreated strings " << split_strings[0] << std::endl;
    }


    prec->vala = prec->a;

    *(float*)prec->valb = get_channel_value(split_strings[0].c_str());
    }
    } catch (std::exception &e) {
        std::cout << e.what();

    } catch (...) {
        puts("Caught unknown exception");
    }

    return 0; /* process output links */
}
