#ifndef ENGINE_INTRO_H
#define ENGINE_INTRO_H

#include <cmath>

#include "utils/ini_configuration.h"
#include "utils/easy_image.h"

namespace intro {
    img::EasyImage color_rectangle(const ini::Configuration &configuration) {
        const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
        const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
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



    img::EasyImage generate_blocks(const ini::Configuration &configuration) {
        const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
        const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
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



    img::EasyImage generate_lines(const ini::Configuration &configuration) {
        const unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
        const unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
        const std::string figure = configuration["LineProperties"]["figure"].as_string_or_die();
        const int N = configuration["LineProperties"]["nrLines"].as_int_or_die();
        std::vector<double> backgroundColor = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
        std::vector<double> lineColor = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();

        img::Color BackgroundColorElement(backgroundColor[0]*255, backgroundColor[1]*255, backgroundColor[2]*255);
        img::EasyImage image(width, height, BackgroundColorElement);
        img::Color lineColorElement(lineColor[0]*255, lineColor[1]*255, lineColor[2]*255);

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
}

#endif //ENGINE_INTRO_H
