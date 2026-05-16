#include <unity.h>
#include <rotator_math.h>  // SPR defaults to 200

// Reference values: SPR=200, ratio=68.4, microstep=1
// Full rotation: 68.4 * 200 * 1 * 360 / 360 = 13680 steps

void setUp(void) {}
void tearDown(void) {}

// --- deg2step ---

void test_deg2step_zero(void) {
    TEST_ASSERT_EQUAL(0, deg2step(0.0f, 68.4f, 1));
}

void test_deg2step_full_rotation(void) {
    TEST_ASSERT_EQUAL(13680, deg2step(360.0f, 68.4f, 1));
}

void test_deg2step_half_rotation(void) {
    TEST_ASSERT_EQUAL(6840, deg2step(180.0f, 68.4f, 1));
}

void test_deg2step_quarter_rotation(void) {
    TEST_ASSERT_EQUAL(3420, deg2step(90.0f, 68.4f, 1));
}

void test_deg2step_microstep_doubles_steps(void) {
    long steps_x1 = deg2step(360.0f, 68.4f, 1);
    long steps_x2 = deg2step(360.0f, 68.4f, 2);
    TEST_ASSERT_EQUAL(steps_x1 * 2, steps_x2);
}

void test_deg2step_pol_ratio(void) {
    // POL_RATIO default: 3.6, full rotation = 3.6 * 200 * 1 = 720 steps
    TEST_ASSERT_EQUAL(720, deg2step(360.0f, 3.6f, 1));
}

// --- step2deg ---

void test_step2deg_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, step2deg(0, 68.4f, 1));
}

void test_step2deg_full_rotation(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 360.0f, step2deg(13680, 68.4f, 1));
}

void test_step2deg_half_rotation(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 180.0f, step2deg(6840, 68.4f, 1));
}

// --- round-trip ---

void test_roundtrip_45deg(void) {
    float original = 45.0f;
    float result = step2deg(deg2step(original, 68.4f, 1), 68.4f, 1);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, original, result);
}

void test_roundtrip_elevation_max(void) {
    float original = 180.0f;
    float result = step2deg(deg2step(original, 68.4f, 1), 68.4f, 1);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, original, result);
}

void test_roundtrip_with_microsteps(void) {
    float original = 90.0f;
    float result = step2deg(deg2step(original, 68.4f, 16), 68.4f, 16);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, original, result);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_deg2step_zero);
    RUN_TEST(test_deg2step_full_rotation);
    RUN_TEST(test_deg2step_half_rotation);
    RUN_TEST(test_deg2step_quarter_rotation);
    RUN_TEST(test_deg2step_microstep_doubles_steps);
    RUN_TEST(test_deg2step_pol_ratio);

    RUN_TEST(test_step2deg_zero);
    RUN_TEST(test_step2deg_full_rotation);
    RUN_TEST(test_step2deg_half_rotation);

    RUN_TEST(test_roundtrip_45deg);
    RUN_TEST(test_roundtrip_elevation_max);
    RUN_TEST(test_roundtrip_with_microsteps);

    return UNITY_END();
}
