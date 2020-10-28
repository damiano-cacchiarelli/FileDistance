cmake_minimum_required(VERSION 3.15)
project(DamianoCacchiarelli105101 C)

set(CMAKE_C_STANDARD 11)

add_executable(filedistance main.c filedistance.c filedistance.h
        distance.c distance.h stack.c stack.h filechange.c filechange.h
        tools.c tools.h search.c search.h sortedlist.c sortedlist.h
        filebuffer.c filebuffer.h)