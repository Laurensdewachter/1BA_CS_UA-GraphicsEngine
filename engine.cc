#include "utils/easy_image.h"
#include "utils/ini_configuration.h"
#include "coordToPixel.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>


img::EasyImage color_rectangle(const unsigned int width, const unsigned int height) {
    img::EasyImage image(width,height);
    const float factor = width/256.0;
    for(unsigned int i = 0; i < width; i++)
    {
        for(unsigned int j = 0; j < height; j++)
        {
            image(i,j).red = round(i/factor);
            image(i,j).green = round(j/factor);
            image(i,j).blue = lround(i/factor+j/factor)%256;
        }
    }
    return image;
}



img::EasyImage generate_blocks(const ini::Configuration &configuration, const unsigned int width, const unsigned int height) {
    const double nrXBlocks = configuration["BlockProperties"]["nrXBlocks"].as_double_or_die();
    const double nrYBlocks = configuration["BlockProperties"]["nrYBlocks"].as_double_or_die();
    std::vector<double> colorWhite = configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
    std::vector<double> colorBlack = configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
    bool invertColors = false;
    configuration["BlockProperties"]["invertColors"].as_bool_if_exists(invertColors);

    img::EasyImage image(width, height);

    if (invertColors) {
        std::vector<double> temp = colorBlack;
        colorBlack = colorWhite;
        colorWhite = temp;
    }

    const double Wb = width/nrXBlocks;
    const double Hb = height/nrYBlocks;

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            const unsigned int Bx = floor(i/Wb);
            const unsigned int By = floor(j/Hb);

            if ((Bx+By)%2 == 0) {
                image(i, j).red = colorWhite[0]*255;
                image(i, j).green = colorWhite[1]*255;
                image(i, j).blue = colorWhite[2]*255;
            }
            else {
                image(i, j).red = colorBlack[0]*255;
                image(i, j).green = colorBlack[1]*255;
                image(i, j).blue = colorBlack[2]*255;
            }
        }
    }
    return image;
}



void quarterCircle(img::EasyImage &image, std::pair<int, int> p1, std::pair<int, int> p2, const int N,
                   img::Color color) {
    int xdir = 1;
    int ydir = 1;
    if (p2.first < p1.first) xdir = -1;
    if (p2.second < p1.second) ydir = -1;

    const double Ws = xdir * (abs(p2.first-p1.first)/(N-1.0));
    const double Hs = ydir * (abs(p2.second-p1.second)/(N-1.0));

    for (int i = 0; i < N; i++) {
        const double p1y = p1.second + i * Hs;
        const double p2x = p1.first + i * Ws;
        image.draw_line(p1.first, lround(p1y), lround(p2x), p2.second, color);
    }
}



img::EasyImage generate_lines(const ini::Configuration &configuration, const unsigned int width, const unsigned int height) {
    const std::string figure = configuration["LineProperties"]["figure"].as_string_or_die();
    const int N = configuration["LineProperties"]["nrLines"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
    std::vector<double> lineColor = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();

    img::Color BackgroundColorElement(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255);
    img::EasyImage image(width, height, BackgroundColorElement);
    img::Color lineColorElement(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255);

    if (figure == "QuarterCircle")
        quarterCircle(image, {0, 0}, {width-1, height-1}, N, lineColorElement);
    else if (figure == "Eye") {
        quarterCircle(image, {0, 0}, {width-1, height-1}, N, lineColorElement);
        quarterCircle(image, {width-1, height-1}, {0, 0}, N, lineColorElement);
    }
    else if (figure == "Diamond") {
        quarterCircle(image, {(width-1)/2, 0}, {width-1, (height-1)/2}, N, lineColorElement);
        quarterCircle(image, {(width-1)/2, height-1}, {0, (height-1)/2}, N, lineColorElement);
        quarterCircle(image, {(width-1)/2, 0}, {0, (height-1)/2}, N, lineColorElement);
        quarterCircle(image, {(width-1)/2, height-1}, {width-1, (height-1)/2}, N, lineColorElement);
    }
    return image;
}



img::EasyImage generate_image(const ini::Configuration &configuration) {
    const std::string type = configuration["General"]["type"].as_string_or_die();
    const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
    const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();

    if (type == "IntroColorRectangle") return color_rectangle(width, height);
    else if (type == "IntroBlocks") return generate_blocks(configuration, width, height);
    else if (type == "IntroLines") return generate_lines(configuration, width, height);
}



int main(int argc, char const* argv[]) {
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName)) {
                                args.push_back(filelistName);
                        }
                }
                for(std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
