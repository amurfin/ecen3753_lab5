#include <stdlib.h>
#include "ctest.h"
#include "priority.h"

// README! - all expected times derived from working out on paper
// process id's and avg times not necessary to test -
// full functionality can be tested by below tests

///////////////////////////////////////////////////////////////////////////////

// priority1 execution[] {3, 5, 4}
// priority1 priority[] {2, 1, 4}
// expected left_to_execute_times {0, 0, 0}
// expected turn times {7, 12, 5}
// expected wait times {4, 7, 1}

CTEST_DATA(priority1) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(priority1) {
    int execution[] = {3, 5, 4};
    int priority[] = {2, 1, 4};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}

// tests that all tasks have completed
CTEST2(priority1, test_left_to_execute_times)
{
    for (int i = 0; i < data->size; i++)
        ASSERT_EQUAL(0, (int)data->task[i].left_to_execute);
}

// tests accurate turn times
CTEST2(priority1, test_turnaround_times)
{
    ASSERT_EQUAL(7, (int)data->task[0].turnaround_time);
    ASSERT_EQUAL(12, (int)data->task[1].turnaround_time);
    ASSERT_EQUAL(5, (int)data->task[2].turnaround_time);
}

// tests accurate wait times
CTEST2(priority1, test_waiting_times)
{
    ASSERT_EQUAL(4, (int)data->task[0].waiting_time);
    ASSERT_EQUAL(7, (int)data->task[1].waiting_time);
    ASSERT_EQUAL(1, (int)data->task[2].waiting_time);
}

///////////////////////////////////////////////////////////////////////////////

// priority2 execution[] {3, 2, 4, 2}
// priority2 priority[] {3, 5, 10, 7}
// expected left_to_execute_times {0, 0, 0, 0}
// expected turn times {11, 8, 6, 3}
// expected wait times {8, 6, 2, 1}

CTEST_DATA(priority2) {
    struct task_t task[4];
    int size;
};

CTEST_SETUP(priority2) {
    int execution[] = {3, 2, 4, 2};
    int priority[] = {3, 5, 10, 7};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}

// tests that all tasks have completed
CTEST2(priority2, test_left_to_execute_times)
{
    for (int i = 0; i < data->size; i++)
        ASSERT_EQUAL(0, (int)data->task[i].left_to_execute);
}

// tests accurate turn times
CTEST2(priority2, test_turnaround_times)
{
  ASSERT_EQUAL(11, (int)data->task[0].turnaround_time);
  ASSERT_EQUAL(8, (int)data->task[1].turnaround_time);
  ASSERT_EQUAL(6, (int)data->task[2].turnaround_time);
  ASSERT_EQUAL(3, (int)data->task[3].turnaround_time);
}

// tests accurate wait times
CTEST2(priority2, test_waiting_times)
{
    ASSERT_EQUAL(8, (int)data->task[0].waiting_time);
    ASSERT_EQUAL(6, (int)data->task[1].waiting_time);
    ASSERT_EQUAL(2, (int)data->task[2].waiting_time);
    ASSERT_EQUAL(1, (int)data->task[3].waiting_time);
}
