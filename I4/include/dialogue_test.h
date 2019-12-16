/**
* @brief It declares the tests for the dialogue module
*
* @file dialogue_test.h
* @author Gonzalo Martín
* @version 2.0
* @date 13-12-2019
*/

#ifndef DIALOGUE_TEST_H
#define DIALOGUE_TEST_H

void test_dialogue_create();

void test_dialogue_destroy();

void test_dialogue_set_last_cmd();

void test_dialogue_set_last_status();

void test_dialogue_set_direction();

void test_dialogue_set_feedback();

void test_dialogue_set_description();

void test_dialogue_get_last_cmd();

void test_dialogue_get_last_status();

void test_dialogue_get_direction();

void test_dialogue_get_feedback();

void test_dialogue_get_description();

void test_dialogue_produce();

#endif
