#include <stdlib.h>
#include <stdio.h>
#include "ctest.h"
#include "sjf.h"
#include <time.h>

///////////////////////////////////////////////////////////////////////////////

// TEST 1 - SJF w/array {1, 2, 3}
// interesting because algorithm shouldn't have to re-order

CTEST_DATA(shortestjobfirst1) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(shortestjobfirst1) {
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst1, test_process_ids) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

CTEST2(shortestjobfirst1, test_execution_times) {
    ASSERT_EQUAL(1, (int)data->task[0].execution_time);
    ASSERT_EQUAL(2, (int)data->task[1].execution_time);
    ASSERT_EQUAL(3, (int)data->task[2].execution_time);
}

CTEST2(shortestjobfirst1, test_waiting_times) {
    ASSERT_EQUAL(0, (int)data->task[0].waiting_time);
    ASSERT_EQUAL(1, (int)data->task[1].waiting_time);
    ASSERT_EQUAL(3, (int)data->task[2].waiting_time);
}

CTEST2(shortestjobfirst1, test_turnaround_times) {
    ASSERT_EQUAL(1, (int)data->task[0].turnaround_time);
    ASSERT_EQUAL(3, (int)data->task[1].turnaround_time);
    ASSERT_EQUAL(6, (int)data->task[2].turnaround_time);
}

CTEST2(shortestjobfirst1, test_avg_times) {
    ASSERT_EQUAL(1.333333, calculate_average_wait_time(data->task, data->size));
    ASSERT_EQUAL(3.333333, calculate_average_turn_around_time(data->task, data->size));
}

///////////////////////////////////////////////////////////////////////////////

// TEST 2 - SJF w/array {2, 1, 4, 4}
// array after order = {1, 2, 4, 4}
// process id order should be 1, 0, 2, 3 (elements 0 and 1 swapped)
// 4 elements and algorithm must re-order w/two duplicate values

CTEST_DATA(shortestjobfirst2) {
    struct task_t task[4];
    int size;
};

CTEST_SETUP(shortestjobfirst2) {
    int execution[] = {2, 1, 4, 4};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst2, test_process_ids) {
    ASSERT_EQUAL(1, (int)data->task[0].process_id);
    ASSERT_EQUAL(0, (int)data->task[1].process_id);
    ASSERT_EQUAL(2, (int)data->task[2].process_id);
    ASSERT_EQUAL(3, (int)data->task[3].process_id);
}

CTEST2(shortestjobfirst2, test_execution_times) {
    ASSERT_EQUAL(1, (int)data->task[0].execution_time);
    ASSERT_EQUAL(2, (int)data->task[1].execution_time);
    ASSERT_EQUAL(4, (int)data->task[2].execution_time);
    ASSERT_EQUAL(4, (int)data->task[3].execution_time);
}

CTEST2(shortestjobfirst2, test_waiting_times) {
    ASSERT_EQUAL(0, (int)data->task[0].waiting_time);
    ASSERT_EQUAL(1, (int)data->task[1].waiting_time);
    ASSERT_EQUAL(3, (int)data->task[2].waiting_time);
    ASSERT_EQUAL(7, (int)data->task[3].waiting_time);
}

CTEST2(shortestjobfirst2, test_turnaround_times) {
    ASSERT_EQUAL(1, (int)data->task[0].turnaround_time);
    ASSERT_EQUAL(3, (int)data->task[1].turnaround_time);
    ASSERT_EQUAL(7, (int)data->task[2].turnaround_time);
    ASSERT_EQUAL(11, (int)data->task[3].turnaround_time);
}

CTEST2(shortestjobfirst2, test_avg_times) {
    ASSERT_EQUAL(2.75, calculate_average_wait_time(data->task, data->size));
    ASSERT_EQUAL(5.5, calculate_average_turn_around_time(data->task, data->size));
}

///////////////////////////////////////////////////////////////////////////////

// TEST 3 - SJF w/array {8, 1, 3, 212, 14, 2}
// array after order = {1, 2, 3, 8, 14, 212}
// process id order should be {1, 5, 2, 0, 4, 3}
// 5 elements and algorithm must re-order lots

CTEST_DATA(shortestjobfirst3) {
    struct task_t task[6];
    int size;
};

CTEST_SETUP(shortestjobfirst3) {
    int execution[] = {8, 1, 3, 212, 14, 2};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst3, test_process_ids) {
    ASSERT_EQUAL(1, (int)data->task[0].process_id);
    ASSERT_EQUAL(5, (int)data->task[1].process_id);
    ASSERT_EQUAL(2, (int)data->task[2].process_id);
    ASSERT_EQUAL(0, (int)data->task[3].process_id);
    ASSERT_EQUAL(4, (int)data->task[4].process_id);
    ASSERT_EQUAL(3, (int)data->task[5].process_id);
}

CTEST2(shortestjobfirst3, test_execution_times) {
    ASSERT_EQUAL(1, (int)data->task[0].execution_time);
    ASSERT_EQUAL(2, (int)data->task[1].execution_time);
    ASSERT_EQUAL(3, (int)data->task[2].execution_time);
    ASSERT_EQUAL(8, (int)data->task[3].execution_time);
    ASSERT_EQUAL(14, (int)data->task[4].execution_time);
    ASSERT_EQUAL(212, (int)data->task[5].execution_time);
}

CTEST2(shortestjobfirst3, test_waiting_times) {
    ASSERT_EQUAL(0, (int)data->task[0].waiting_time);
    ASSERT_EQUAL(1, (int)data->task[1].waiting_time);
    ASSERT_EQUAL(3, (int)data->task[2].waiting_time);
    ASSERT_EQUAL(6, (int)data->task[3].waiting_time);
    ASSERT_EQUAL(14, (int)data->task[4].waiting_time);
    ASSERT_EQUAL(28, (int)data->task[5].waiting_time);
}

CTEST2(shortestjobfirst3, test_turnaround_times) {
    ASSERT_EQUAL(1, (int)data->task[0].turnaround_time);
    ASSERT_EQUAL(3, (int)data->task[1].turnaround_time);
    ASSERT_EQUAL(6, (int)data->task[2].turnaround_time);
    ASSERT_EQUAL(14, (int)data->task[3].turnaround_time);
    ASSERT_EQUAL(28, (int)data->task[4].turnaround_time);
    ASSERT_EQUAL(240, (int)data->task[5].turnaround_time);
}

CTEST2(shortestjobfirst3, test_avg_times) {
    ASSERT_EQUAL(8.666666, calculate_average_wait_time(data->task, data->size));
    ASSERT_EQUAL(48.666666, calculate_average_turn_around_time(data->task, data->size));
}
