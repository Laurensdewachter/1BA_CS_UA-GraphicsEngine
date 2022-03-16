#include "2DLSystem.h"

img::EasyImage LSystem2D::LSystem2D(const ini::Configuration &configuration) {
    const unsigned int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color BackgroundColorElement(backgroundColor[0]*255, backgroundColor[1]*255, backgroundColor[2]*255);
    std::vector<double> lineColor = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    img::Color LineColorElement(lineColor[0]*255, lineColor[1]*255, lineColor[2]*255);
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();

    LParser::LSystem2D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    const std::set<char> alphabet = l_system.get_alphabet();
    std::string initiator = l_system.get_initiator();
    const double angle = l_system.get_angle();
    const double starting_angle = l_system.get_starting_angle();
    const unsigned int iterations = l_system.get_nr_iterations();
    std::map<char, bool> draw;
    std::map<char, std::string> replacements;
    for (auto i : alphabet) {
        draw[i] = l_system.draw(i);
        replacements[i] = l_system.get_replacement(i);
    }

    for (unsigned int i = 0; i < iterations; i++) {
        std::string replacement;
        for (auto j : initiator) {
            if (j == '+') replacement += "+";
            if (j == '-') replacement += "-";
            if (j == '(') replacement += "(";
            if (j == ')') replacement += ")";
            else replacement += replacements[j];
        }
        initiator = replacement;
    }

    Point2D cur_point;
    cur_point.x = 0;
    cur_point.y = 0;
    double cur_dir = starting_angle;
    Lines2D lines;
    Line2D new_line;
    std::stack<Point2D> points_stack;
    std::stack<double> dir_stack;
    for (auto i : initiator) {
        if (i == '+') cur_dir += angle;
        else if (i == '-') cur_dir -= angle;
        else if (i == '(') {
            points_stack.push(cur_point);
            dir_stack.push(cur_dir);
        }
        else if (i == ')') {
            Point2D temp_point = points_stack.top();
            points_stack.pop();
            cur_point.x = temp_point.x;
            cur_point.y = temp_point.y;

            cur_dir = dir_stack.top();
            dir_stack.pop();
        }
        else {
            Point2D new_point;
            new_point.x = cur_point.x + cos((cur_dir*M_PI)/180.0);
            new_point.y = cur_point.y + sin((cur_dir*M_PI)/180.0);
            if (draw[i]) {
                new_line.p1 = cur_point;
                new_line.p2 = new_point;
                new_line.color = LineColorElement;
                lines.push_back(new_line);
            }
            cur_point = new_point;
        }
    }
    return coordToPixel(lines, size, BackgroundColorElement);
}