// **************************************************
// ***************BELT SPEED SETTINGS ***************
// **************************************************
// The variables below control the speeds and timings of the desired perturbation profile
// The profiles are defined in terms of speed and duration
// So, the first item in speed is run for as long as the time listed in the first interval
// The speed profile is defined in terms of motor RPM
// The timing interval is defined in terms of milliseconds (1000 ms = 1s)
// ***NOTE*** - The number of items in speed MUST equal the number of items in interval for their respective sides
//            - Left and Right do not have to have the same number of items
const int TestSpeed5L[] = {128, 139, 150, 161, 172, 182, 193, 204, 215, 226, 237, 248, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 252, 252, 251, 251, 250, 250, 250, 249, 249, 248, 248, 248, 247, 247, 246, 246, 245, 245, 245, 244, 244, 243, 243, 243, 242, 242, 241, 241, 241, 240, 240, 239, 239, 239, 238, 238, 237, 237, 237, 236, 236, 235, 235, 234, 234, 234, 233, 233, 232, 232, 232, 231, 231, 230, 230, 230, 229, 229, 228, 228, 228, 227, 227, 226, 226, 225, 225, 225, 224, 224, 223, 223, 223, 222, 222, 221, 221, 221, 220, 220, 219, 219, 219, 218, 218, 217, 217, 217, 216, 216, 215, 215, 214, 214, 214, 213, 213, 212, 212, 212, 211, 211, 210, 210, 210, 209, 209, 208, 208, 208, 207, 207, 206, 206, 206, 205, 205, 204, 204, 203, 203, 203, 202, 202, 201, 201, 201, 200, 200, 199, 199, 199, 198, 198, 197, 197, 197, 196, 196, 195, 195, 194, 194, 194, 193, 193, 192, 192, 192, 191, 191, 190, 190, 190, 189, 189, 188, 188, 188, 187, 187, 186, 186, 186, 185, 185, 184, 184, 183, 183, 183, 182, 182, 181, 181, 181, 180, 180, 179, 179, 179, 178, 178, 177, 177, 177, 176, 176, 175, 175, 175, 174, 174, 173, 173, 172, 172, 172, 171, 171, 170, 170, 170, 169, 169, 168, 168, 168, 167, 167, 166, 166, 166, 165, 165, 164, 164, 163, 163, 163, 162, 162, 161, 161, 161, 160, 160, 159, 159, 159, 158, 158, 157, 157, 157, 156, 156, 155, 155, 155, 154, 154, 153, 153, 152, 152, 152, 151, 151, 150, 150, 150, 149, 149, 148, 148, 148, 147, 147, 146, 146, 146, 145, 145, 144, 144, 144, 143, 143, 142, 142, 141, 141, 141, 140, 140, 139, 139, 139, 138, 138, 137, 137, 137, 136, 136, 135, 135, 135, 134, 134, 133, 133, 132, 132, 132, 131, 131, 130, 130, 130, 129, 129, 128, 128};
const int TestSpeed5R[] = {128, 117, 106, 95, 84, 74, 63, 52, 41, 30, 20, 9, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 15, 16, 16, 17, 17, 17, 18, 18, 19, 19, 19, 20, 20, 21, 21, 21, 22, 22, 23, 23, 23, 24, 24, 25, 25, 26, 26, 26, 27, 27, 28, 28, 28, 29, 29, 30, 30, 30, 31, 31, 32, 32, 32, 33, 33, 34, 34, 34, 35, 35, 36, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 45, 46, 46, 47, 47, 47, 48, 48, 49, 49, 49, 50, 50, 51, 51, 51, 52, 52, 53, 53, 53, 54, 54, 55, 55, 55, 56, 56, 57, 57, 57, 58, 58, 59, 59, 60, 60, 60, 61, 61, 62, 62, 62, 63, 63, 64, 64, 64, 65, 65, 66, 66, 66, 67, 67, 68, 68, 68, 69, 69, 70, 70, 70, 71, 71, 72, 72, 72, 73, 73, 74, 74, 74, 75, 75, 76, 76, 77, 77, 77, 78, 78, 79, 79, 79, 80, 80, 81, 81, 81, 82, 82, 83, 83, 83, 84, 84, 85, 85, 85, 86, 86, 87, 87, 87, 88, 88, 89, 89, 89, 90, 90, 91, 91, 91, 92, 92, 93, 93, 94, 94, 94, 95, 95, 96, 96, 96, 97, 97, 98, 98, 98, 99, 99, 100, 100, 100, 101, 101, 102, 102, 102, 103, 103, 104, 104, 104, 105, 105, 106, 106, 106, 107, 107, 108, 108, 108, 109, 109, 110, 110, 111, 111, 111, 112, 112, 113, 113, 113, 114, 114, 115, 115, 115, 116, 116, 117, 117, 117, 118, 118, 119, 119, 119, 120, 120, 121, 121, 121, 122, 122, 123, 123, 123, 124, 124, 125, 125, 125, 126, 126, 127, 127, 128};
const int TestTiming5[] = {0, 25, 50, 75, 100, 125, 150, 176, 201, 226, 251, 276, 301, 326, 351, 376, 401, 426, 451, 476, 502, 527, 552, 577, 602, 627, 652, 677, 702, 727, 752, 777, 802, 827, 853, 878, 903, 928, 953, 978, 1003, 1028, 1053, 1078, 1103, 1128, 1153, 1179, 1204, 1229, 1254, 1279, 1304, 1329, 1354, 1379, 1404, 1429, 1454, 1479, 1505, 1530, 1555, 1580, 1605, 1630, 1655, 1680, 1705, 1730, 1755, 1780, 1805, 1831, 1856, 1881, 1906, 1931, 1956, 1981, 2006, 2031, 2056, 2081, 2106, 2131, 2156, 2182, 2207, 2232, 2257, 2282, 2307, 2332, 2357, 2382, 2407, 2432, 2457, 2482, 2508, 2533, 2558, 2583, 2608, 2633, 2658, 2683, 2708, 2733, 2758, 2783, 2808, 2834, 2859, 2884, 2909, 2934, 2959, 2984, 3009, 3034, 3059, 3084, 3109, 3134, 3160, 3185, 3210, 3235, 3260, 3285, 3310, 3335, 3360, 3385, 3410, 3435, 3460, 3485, 3511, 3536, 3561, 3586, 3611, 3636, 3661, 3686, 3711, 3736, 3761, 3786, 3811, 3837, 3862, 3887, 3912, 3937, 3962, 3987, 4012, 4037, 4062, 4087, 4112, 4137, 4163, 4188, 4213, 4238, 4263, 4288, 4313, 4338, 4363, 4388, 4413, 4438, 4463, 4489, 4514, 4539, 4564, 4589, 4614, 4639, 4664, 4689, 4714, 4739, 4764, 4789, 4815, 4840, 4865, 4890, 4915, 4940, 4965, 4990, 5015, 5040, 5065, 5090, 5115, 5140, 5166, 5191, 5216, 5241, 5266, 5291, 5316, 5341, 5366, 5391, 5416, 5441, 5466, 5492, 5517, 5542, 5567, 5592, 5617, 5642, 5667, 5692, 5717, 5742, 5767, 5792, 5818, 5843, 5868, 5893, 5918, 5943, 5968, 5993, 6018, 6043, 6068, 6093, 6118, 6144, 6169, 6194, 6219, 6244, 6269, 6294, 6319, 6344, 6369, 6394, 6419, 6444, 6469, 6495, 6520, 6545, 6570, 6595, 6620, 6645, 6670, 6695, 6720, 6745, 6770, 6795, 6821, 6846, 6871, 6896, 6921, 6946, 6971, 6996, 7021, 7046, 7071, 7096, 7121, 7147, 7172, 7197, 7222, 7247, 7272, 7297, 7322, 7347, 7372, 7397, 7422, 7447, 7473, 7498, 7523, 7548, 7573, 7598, 7623, 7648, 7673, 7698, 7723, 7748, 7773, 7798, 7824, 7849, 7874, 7899, 7924, 7949, 7974, 7999, 8024, 8049, 8074, 8099, 8124, 8150, 8175, 8200, 8225, 8250, 8275, 8300};
const int NumSpaces5 = sizeof(TestTiming5) / sizeof(TestTiming5[0]);

const int TestSpeed3L[] = {128, 135, 143, 150, 158, 165, 173, 180, 188, 195, 203, 210, 217, 217, 216, 216, 216, 215, 215, 215, 214, 214, 213, 213, 213, 212, 212, 212, 211, 211, 210, 210, 210, 209, 209, 209, 208, 208, 207, 207, 207, 206, 206, 206, 205, 205, 204, 204, 204, 203, 203, 203, 202, 202, 201, 201, 201, 200, 200, 200, 199, 199, 198, 198, 198, 197, 197, 197, 196, 196, 195, 195, 195, 194, 194, 194, 193, 193, 192, 192, 192, 191, 191, 191, 190, 190, 189, 189, 189, 188, 188, 188, 187, 187, 186, 186, 186, 185, 185, 185, 184, 184, 183, 183, 183, 182, 182, 182, 181, 181, 180, 180, 180, 179, 179, 179, 178, 178, 177, 177, 177, 176, 176, 176, 175, 175, 174, 174, 174, 173, 173, 173, 172, 172, 171, 171, 171, 170, 170, 170, 169, 169, 168, 168, 168, 167, 167, 167, 166, 166, 165, 165, 165, 164, 164, 164, 163, 163, 162, 162, 162, 161, 161, 161, 160, 160, 159, 159, 159, 158, 158, 158, 157, 157, 156, 156, 156, 155, 155, 155, 154, 154, 153, 153, 153, 152, 152, 152, 151, 151, 150, 150, 150, 149, 149, 149, 148, 148, 147, 147, 147, 146, 146, 146, 145, 145, 144, 144, 144, 143, 143, 143, 142, 142, 141, 141, 141, 140, 140, 140, 139, 139, 138, 138, 138, 137, 137, 137, 136, 136, 135, 135, 135, 134, 134, 134, 133, 133, 132, 132, 132, 131, 131, 131, 130, 130, 129, 129, 129, 128, 128, 128};
const int TestSpeed3R[] = {128, 120, 112, 105, 97, 90, 82, 75, 67, 60, 52, 45, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 48, 48, 48, 49, 49, 49, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 63, 63, 63, 64, 64, 64, 65, 65, 66, 66, 66, 67, 67, 67, 68, 68, 69, 69, 69, 70, 70, 70, 71, 71, 72, 72, 72, 73, 73, 73, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 78, 78, 78, 79, 79, 79, 80, 80, 81, 81, 81, 82, 82, 82, 83, 83, 84, 84, 84, 85, 85, 85, 86, 86, 87, 87, 87, 88, 88, 88, 89, 89, 90, 90, 90, 91, 91, 91, 92, 92, 93, 93, 93, 94, 94, 94, 95, 95, 96, 96, 96, 97, 97, 97, 98, 98, 99, 99, 99, 100, 100, 100, 101, 101, 102, 102, 102, 103, 103, 103, 104, 104, 105, 105, 105, 106, 106, 106, 107, 107, 108, 108, 108, 109, 109, 109, 110, 110, 111, 111, 111, 112, 112, 112, 113, 113, 114, 114, 114, 115, 115, 115, 116, 116, 117, 117, 117, 118, 118, 118, 119, 119, 120, 120, 120, 121, 121, 121, 122, 122, 123, 123, 123, 124, 124, 124, 125, 125, 126, 126, 126, 127, 127, 128};
const int TestTiming3[] = {0, 25, 50, 75, 100, 125, 151, 176, 201, 226, 251, 276, 301, 326, 351, 376, 402, 427, 452, 477, 502, 527, 552, 577, 602, 627, 653, 678, 703, 728, 753, 778, 803, 828, 853, 878, 904, 929, 954, 979, 1004, 1029, 1054, 1079, 1104, 1129, 1155, 1180, 1205, 1230, 1255, 1280, 1305, 1330, 1355, 1380, 1406, 1431, 1456, 1481, 1506, 1531, 1556, 1581, 1606, 1631, 1657, 1682, 1707, 1732, 1757, 1782, 1807, 1832, 1857, 1882, 1908, 1933, 1958, 1983, 2008, 2033, 2058, 2083, 2108, 2133, 2159, 2184, 2209, 2234, 2259, 2284, 2309, 2334, 2359, 2384, 2410, 2435, 2460, 2485, 2510, 2535, 2560, 2585, 2610, 2635, 2661, 2686, 2711, 2736, 2761, 2786, 2811, 2836, 2861, 2886, 2912, 2937, 2962, 2987, 3012, 3037, 3062, 3087, 3112, 3137, 3163, 3188, 3213, 3238, 3263, 3288, 3313, 3338, 3363, 3388, 3414, 3439, 3464, 3489, 3514, 3539, 3564, 3589, 3614, 3639, 3665, 3690, 3715, 3740, 3765, 3790, 3815, 3840, 3865, 3890, 3916, 3941, 3966, 3991, 4016, 4041, 4066, 4091, 4116, 4141, 4167, 4192, 4217, 4242, 4267, 4292, 4317, 4342, 4367, 4392, 4418, 4443, 4468, 4493, 4518, 4543, 4568, 4593, 4618, 4643, 4669, 4694, 4719, 4744, 4769, 4794, 4819, 4844, 4869, 4894, 4920, 4945, 4970, 4995, 5020, 5045, 5070, 5095, 5120, 5145, 5171, 5196, 5221, 5246, 5271, 5296, 5321, 5346, 5371, 5396, 5422, 5447, 5472, 5497, 5522, 5547, 5572, 5597, 5622, 5647, 5673, 5698, 5723, 5748, 5773, 5798, 5823, 5848, 5873, 5898, 5924, 5949, 5974, 5999, 6024, 6049, 6074, 6099, 6124, 6149, 6175, 6200, 6225, 6250, 6275, 6300};
const int NumSpaces3 = sizeof(TestTiming3) / sizeof(TestTiming3[0]);

const int TestSpeed2L[] = {128, 132, 137, 141, 146, 150, 155, 159, 164, 168, 173, 177, 181, 181, 181, 180, 180, 180, 179, 179, 179, 178, 178, 178, 177, 177, 177, 176, 176, 176, 175, 175, 175, 174, 174, 173, 173, 173, 172, 172, 172, 171, 171, 171, 170, 170, 170, 169, 169, 169, 168, 168, 168, 167, 167, 167, 166, 166, 166, 165, 165, 165, 164, 164, 164, 163, 163, 163, 162, 162, 162, 161, 161, 161, 160, 160, 160, 159, 159, 159, 158, 158, 158, 157, 157, 157, 156, 156, 156, 155, 155, 155, 154, 154, 154, 153, 153, 153, 152, 152, 152, 151, 151, 150, 150, 150, 149, 149, 149, 148, 148, 148, 147, 147, 147, 146, 146, 146, 145, 145, 145, 144, 144, 144, 143, 143, 143, 142, 142, 142, 141, 141, 141, 140, 140, 140, 139, 139, 139, 138, 138, 138, 137, 137, 137, 136, 136, 136, 135, 135, 135, 134, 134, 134, 133, 133, 133, 132, 132, 132, 131, 131, 131, 130, 130, 130, 129, 129, 129, 128, 128, 128};
const int TestSpeed2R[] = {128, 123, 118, 114, 109, 105, 100, 96, 91, 87, 82, 78, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 77, 78, 78, 78, 79, 79, 79, 80, 80, 80, 81, 81, 82, 82, 82, 83, 83, 83, 84, 84, 84, 85, 85, 85, 86, 86, 86, 87, 87, 87, 88, 88, 88, 89, 89, 89, 90, 90, 90, 91, 91, 91, 92, 92, 92, 93, 93, 93, 94, 94, 94, 95, 95, 95, 96, 96, 96, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100, 100, 101, 101, 101, 102, 102, 102, 103, 103, 103, 104, 104, 105, 105, 105, 106, 106, 106, 107, 107, 107, 108, 108, 108, 109, 109, 109, 110, 110, 110, 111, 111, 111, 112, 112, 112, 113, 113, 113, 114, 114, 114, 115, 115, 115, 116, 116, 116, 117, 117, 117, 118, 118, 118, 119, 119, 119, 120, 120, 120, 121, 121, 121, 122, 122, 122, 123, 123, 123, 124, 124, 124, 125, 125, 125, 126, 126, 126, 127, 127, 128};
const int TestTiming2[] = {0, 25, 50, 75, 101, 126, 151, 176, 201, 226, 251, 277, 302, 327, 352, 377, 402, 427, 453, 478, 503, 528, 553, 578, 604, 629, 654, 679, 704, 729, 754, 780, 805, 830, 855, 880, 905, 930, 956, 981, 1006, 1031, 1056, 1081, 1106, 1132, 1157, 1182, 1207, 1232, 1257, 1282, 1308, 1333, 1358, 1383, 1408, 1433, 1458, 1484, 1509, 1534, 1559, 1584, 1609, 1635, 1660, 1685, 1710, 1735, 1760, 1785, 1811, 1836, 1861, 1886, 1911, 1936, 1961, 1987, 2012, 2037, 2062, 2087, 2112, 2137, 2163, 2188, 2213, 2238, 2263, 2288, 2313, 2339, 2364, 2389, 2414, 2439, 2464, 2489, 2515, 2540, 2565, 2590, 2615, 2640, 2665, 2691, 2716, 2741, 2766, 2791, 2816, 2842, 2867, 2892, 2917, 2942, 2967, 2992, 3018, 3043, 3068, 3093, 3118, 3143, 3168, 3194, 3219, 3244, 3269, 3294, 3319, 3344, 3370, 3395, 3420, 3445, 3470, 3495, 3520, 3546, 3571, 3596, 3621, 3646, 3671, 3696, 3722, 3747, 3772, 3797, 3822, 3847, 3873, 3898, 3923, 3948, 3973, 3998, 4023, 4049, 4074, 4099, 4124, 4149, 4174, 4199, 4225, 4250, 4275, 4300};
const int NumSpaces2 = sizeof(TestTiming2) / sizeof(TestTiming2[0]);


int aFastStor [] =    {    -5,    -5,    8,     -12,   -12};
//float aFastStor [] =    {    -5,    -5,    0,     -12,   -12};
float VmaxStor [] =   {  1.5,  1.5,  2.5,    3.6,  3.6};
float dtStor [] =    {  0.3,  0.3,  0.3,    0.3,  0.3};
float dtSlowStor [] = {0.3,  0.3,  0.3,    0.3,  0.3};
//float dtSlowStor [] = {dtStor[1],    4,    6,  dtStor[4],    8};
int aSlowStor [] =  {    5,    5,    8,     12,   12};
//float aSlowStor [] =  {aFastStor[1] * -1, 0, 0, aFastStor[4] * -1, 0};
int vi = 0;
float Vmax;
float dtSlow;

// Initialize array thats arbitrarily large to store motor speed and timnig values
int LeftSpeedProfile4 [100];
int LeftMotorTiming4 [100];

const int RightSpeedProfile4 [100];
const int RightMotorTiming4 [100];

// Determine the length of the profile, used to changes
const byte LeftSpeedLength4 = (sizeof(LeftSpeedProfile4) / sizeof(LeftSpeedProfile4[0]));
const byte RightSpeedLength4 = (sizeof(RightSpeedProfile4) / sizeof(RightSpeedProfile4[0]));

//
int LeftTiming [100];
int RightTiming [100];

//byte LeftSpeedPWM2 [LeftSpeedLength2];
//byte RightSpeedPWM2 [RightSpeedLength2];
//byte LeftSpeedPWM3 [LeftSpeedLength3];
//byte RightSpeedPWM3 [RightSpeedLength3];

int LeftSpeedPWM [100];
int RightSpeedPWM [100];

// **************************************************
// ***************** Hardware Pins ******************
// **************************************************
// Define the Arduino pins that hardware is connected to

// ******************* MOTOR PINS *******************
//  Both motors have 4 pins for communication
//  Enable Pin turns on the motor,
//        Enable = High, motors active
//        Enable = Low, motors inactive
//  Input A Pin is the Inhibit Pin.  This forces the belt speed to zero, overiding other inputs.
//        The function of this is simillar to the enable pin, but it does so without shutting down the motors,
//        so the pin state of the other inputs can still be monitored in ClearPath.
//        Input A = Low, motion enabled
//        Input A = High, motion disabled.
//  Input B Pin is the PWM pin, the motors read a PWM signal sent over this pin whose duty cycle represents the desired veolcity
//        Duty Cucle = 0% commands max speed in CCW direction
//        Duty Cycle = 100% commands max speed in CW direction
//        Duty Cycle = 50% commands zero speed
//        The max speed is set using the ClearPath software, and is a function of input voltage
//  HLFB Pin is an output pin, as in the motors output data that can be read by the arduino over this pin.
//        There are many modes this output can represent, see the ClearPath user manual
//        It is currently being used to output a PWM signal proportional the the motor speed.
//        But it also can output torque, pulses per revolution, system power on, among many othres

const int Left_Enable_Pin =  53; // the pin number of the ENABLE pin
const int Left_InputA_Pin =  4 ; // the pin number of the InputA pin, the Inhibit Pin
const int Left_InputB_Pin =  5 ; // the pin number of the InputB pin, needs to be pins 2 - 13, 44 - 46 for PWM
const int Left_HLFB_Pin = 18;    // the pin number of the HLFB pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA

const int Right_Enable_Pin =  52 ; // the pin number of the ENABLE pin
const int Right_InputA_Pin =  6 ;  // the pin number of the InputA pin, the Inhibit Pin
const int Right_InputB_Pin =  7 ;  // the pin number of the InputB pin, needs to be pins 2 - 13, 44 - 46 for PWM
const int Right_HLFB_Pin = 19;     // the pin number of the HLFB pin, used in PWM ISR, has to be pin 2, 3, 18, 19 on MEAGA

// Estop
const int Estop_pin = 2;  // Define Estop pin

// Rotary Switch
const int SwitchPin1 = 31;
const int SwitchPin2 = 29;
const int SwitchPin3 = 27;
const int SwitchPin4 = 25;
const int SwitchPin5 = 23;

// PushButton
const int TriggerOnPin = 3;
const int TriggerOffPin = 8;

// LEDs
const int RedLEDpin = 39;
const int GreenLEDpin = 37;
const int PWRLEDpin = 9;

// Belst Select Toggle Switch
const int SwitchLeftPin = 51;
const int SwitchRightPin = 50;

// Belt Speed Potentiometer
const int PotPin = A0;


// **************************************************
// **************** Global Variables ****************
// **************************************************
//  Initialize variables for reading PWM values, used in PWM_ISRs
volatile float LeftHighTime = 0;  // USed in PWM_A_Falling ISR ***THIS VALUE WE NEED TO STORE IN MEMORY CARD***
volatile float LeftRiseTime = 0;  // Used in Left_PWM_Rising ISR
volatile float LeftPeriodTime = 0;// Used in Left_PWM_Rising ISR
int PrevousLeftHighTime = 0;    // Used in comparator to check if change has occurred in PWM A Value

volatile float RightHighTime = 0;  // USed in PWM_B_Falling ISR ***THIS VALUE WE NEED TO STORE IN MEMORY CARD***
volatile float RightRiseTime = 0;  // Used in Right_PWM_Rising ISR
volatile float RightPeriodTime = 0;// Used in Right_PWM_Rising ISR
int PrevousRightHighTime = 0;     // Used in comparator to check if change has occurred in PWM B Value

int LeftDutyCycle;
int RightDutyCycle;

// Variables for Trigger
volatile int TriggerISR = 0;          // Volatile needed so so varibale can be read and modified outside of ISR
const int TriggerDebounceDelay = 100;
int CurrentPushTime;
int LastPushTime;
byte TriggerMode;

// Variables for timing
unsigned long StartMillis;
unsigned long currentMillis;

// Variables for mmotor controller
int LeftStage = 0;
int RightStage = 0;

int stage = 0;
int MotorSpeed;
int OldMotorSpeed;

// Settings for 2-way communication on mode 5
byte i = 0; // Controlls loop for mode 5
byte ReadBeltSpeed = 0;  // Controls read  data loop in mode 5
int NewBeltSpeed [4];

// Variables For EStop State
bool EstopState;


// Varriables for Potentiometer
float WalkingSpeed;

// Varrialbes for Belt Select Toggle Switch
byte SelectState;

// Variables for PerturbationProfile
const int MaxMotorRPM = 2200;
float aSlow;
float BeltAccel;
float dT;
//float dTslow;
int NumSpaces;
float MotorTiming[100];
float MotorVel[100];
float MotorRPM[100];
byte MotorPWM[100];
//int MotorTiming;
//float MotorRPM[350];
//float MotorVel;

// Varriables for Safety Systems
bool EstopSafetyDisable;

byte OperatingMode;

//  Begin Setup Loop, this only runs once during startup.
void setup() {
  // Begin Serial Output
  //Serial.begin(9600);   // Uncomment if using the Arduino Serial Monitor
  Serial.begin(250000);   // Uncomment if using the Matlab Serial Monitor
  delay(2000);      // Wait for predetermined amount of time before continuing so serial monitor doesn’t output garbage
  Serial.println();

  // Define inut and output pins
  pinMode(Left_Enable_Pin, OUTPUT);
  pinMode(Left_InputA_Pin, OUTPUT);
  pinMode(Left_InputB_Pin, OUTPUT);

  pinMode(Right_Enable_Pin, OUTPUT);
  pinMode(Right_InputA_Pin, OUTPUT);
  pinMode(Right_InputB_Pin, OUTPUT);

  pinMode(Estop_pin, INPUT_PULLUP);
  pinMode(Left_HLFB_Pin, INPUT_PULLUP);
  pinMode(Right_HLFB_Pin, INPUT_PULLUP);

  // Define Switch pins as inputs
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(SwitchPin5, INPUT_PULLUP);

  pinMode(TriggerOffPin, INPUT_PULLUP);
  pinMode(TriggerOnPin, INPUT_PULLUP);

  pinMode(SwitchLeftPin, INPUT_PULLUP);
  pinMode(SwitchRightPin, INPUT_PULLUP);

  pinMode(RedLEDpin, OUTPUT);
  pinMode(GreenLEDpin, OUTPUT);
  pinMode(PWRLEDpin, OUTPUT);

  digitalWrite(RedLEDpin, LOW);
  digitalWrite(GreenLEDpin, LOW);

  attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING);   //Create ISR to monitor for changes in Trigger state

  //attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), Left_PWM_Rising, RISING);
  //attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), Right_PWM_Rising, RISING);

  EstopSafetyDisable = 1; // Dont allow motion to begin if the belt speed is at a non zero state when the device is first turned on

  for (int i = 0; i < 5; i++) {
    if (aFastStor[i] == 0 && VmaxStor[i] != 0) {
      aFastStor[i] = (VmaxStor[i] - vi) / dtStor[i];
    }
    if (aSlowStor[i] == 0 && dtSlowStor[i] != 0) {
      aSlowStor[i] = (vi - VmaxStor[i]) / dtSlowStor[i];
    }
    Serial.print("Mode ");
    Serial.print(i);
    Serial.print(", aFast =");
    Serial.print(aFastStor[i]);
    Serial.print(", aSlow =");
    Serial.println(aSlowStor[i]);
  }
  Serial.println(NumSpaces5);
  Serial.println(NumSpaces3);
  Serial.println(NumSpaces2);
}

void loop() {

  // Estop - disables motors if its engaged
  EstopState = digitalRead(Estop_pin);
  static bool PrevousEstopState;
  if (EstopState == 1) {
    // This forces the motors to disable every loop iteration even if another function is trying to enable them.
    digitalWrite(Right_InputA_Pin, HIGH);
    digitalWrite(Left_InputA_Pin, HIGH);
    digitalWrite(RedLEDpin, HIGH);
    PrevousEstopState = 1;
    Serial.println("EStop");
  }
  else if (PrevousEstopState != EstopState) {
    Serial.println("EStop Disengaged");
    Serial.println("Return Belt Speed To Zero To Re-Enable Motion");
    digitalWrite(RedLEDpin, LOW);
    PrevousEstopState = 0;
    EstopSafetyDisable = 1;   // Flag to not allow belt motion untill belt speed is reset to zero
  }

  currentMillis = millis(); // Store time starting since the device was turned on, milliseconds

  // Belt Toggle Switch, lets user sselect between left, right or both belts
  static bool RecalcPerturbationProfile = 1; // Flag to store if Perturbation Profile needs to be recalculated, set to 1 so it auto executes on the first cycle
  static byte PrevousSelectState = 0;
  SelectState = digitalRead(SwitchLeftPin) + digitalRead(SwitchRightPin) * 2;
  if (SelectState != PrevousSelectState) {
    switch (SelectState) {
      case 1:
        Serial.println("Left");
        break;
      case 2:
        Serial.println("Right");
        break;
      case 3:
        Serial.println("BOTH");
        break;
    }
    PrevousSelectState = SelectState; // this is used to make the loop only run once, after state change
    RecalcPerturbationProfile = 1;  // Set flag high to recalculate perturbation profile
  }

  // Mode Switch, used to different operating modes, with different belt speed settings
  static byte SwitchPosition;
  static byte PrevousSwitchPosition = 8;  // initially set arbitrarily large so current switch position is read

  SwitchPosition = (-9) + (digitalRead(SwitchPin1) * 1) + (digitalRead(SwitchPin2) * 2) + (digitalRead(SwitchPin3) * 3) + (digitalRead(SwitchPin4) * 4) + (digitalRead(SwitchPin5) * 5);
  if (PrevousSwitchPosition != SwitchPosition && SwitchPosition != 6) {
    RecalcPerturbationProfile = 1;  // Profile needs to be reculculated if switch has changed positions
    TriggerMode = 0;// Reset trigger so belt speed profiles dont continue to run when the switch changes position
    digitalWrite(GreenLEDpin, LOW); // Turn off Trigger LED
    LeftStage = 0;  // Reset belt stage so belt speed profiles starts at begining
    RightStage = 0;
    switch (SwitchPosition) {
      case 1:
        Serial.println("Position 1");
        OperatingMode = 1;
        BeltAccel = -5;
        dT = 0.3;
        aSlow = 5;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        //aSlow = 1;
        break;
      case 2:
        Serial.println("Position 2");
        OperatingMode = 2;
        BeltAccel = -5;
        dT = 0.3;
        aSlow = 2;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        break;
      case 3:
        Serial.println("Position 3");
        OperatingMode = 3;
        BeltAccel = -8;
        dT = 0.3;
        aSlow = 2;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        break;
      case 4:
        Serial.println("Position 4");
        OperatingMode = 4;
        BeltAccel = -12;
        dT = 0.3;
        aSlow = 9;
        //aSlow = BeltAccel * - 1;
        break;
      case 5:
        Serial.println("Position 5");
        OperatingMode = 5;
        BeltAccel = -12;
        dT = 0.3;
        aSlow = 2;
        //BeltAccel = aFastStor[OperatingMode - 1];
        //dT = dtStor[OperatingMode - 1];
        //aSlow = aSlowStor[OperatingMode - 1];
        //dtSlow = dtSlowStor[OperatingMode - 1];
        //Vmax = VmaxStor[OperatingMode - 1];
        break;
      case 6:
        Serial.println("ERROR");
        break;
    }
    PrevousSwitchPosition = SwitchPosition; // Set prevous value to current value so loop only executes on state change
  }

  // Read Potentiometer to Determine Walking Speed
  static byte PrevousPotState = 0;
  byte PotState = map(analogRead(PotPin), 0, 1024, 0, 255); // Map to byte, used to reduce noise
  if (abs(PotState - PrevousPotState) >= 2) { // Only update if a large enough change has occoured
    //float WalkingSpeed = (PotState - 0) * (1.25 - -1.25) / (255 - 0) + -1.25;
    // Maps PotState to Belt Speed,
    // Map is used twice to reduce number of floating point calculations in main loop
    WalkingSpeed = (0.0098039 * PotState - 1.25);

    //WalkingSpeed = (0.0529*PotState + 127.5000);
    if (abs(WalkingSpeed) <= 0.05) {  // Set Walking speed to 0 if its close to 0
      WalkingSpeed = 0;
    }
    if (SelectState == 1) {
      digitalWrite(Left_Enable_Pin, HIGH);
    }
    Serial.print("Pot Reading = ");
    Serial.print(PotState);
    Serial.print(", Belt Speed = ");
    Serial.println(WalkingSpeed);
    analogWrite(PWRLEDpin, PotState);  // Change Power LED brightness based of reading, just for fun
    PrevousPotState = PotState;
    RecalcPerturbationProfile = 1;
  }

  if (RecalcPerturbationProfile == 1) {
    PerturbationProfile(WalkingSpeed, BeltAccel, dT);
    RecalcPerturbationProfile = 0;
  }

  if (EstopSafetyDisable == 1) {
    digitalWrite(Right_InputA_Pin, HIGH);  // Pull Inhibit pin hight to disallow motion without shutting down motors
    digitalWrite(Left_InputA_Pin, HIGH);
    bool LEDstate = 1;
    while (EstopSafetyDisable == 1) {     // Loop untill Belt motion is reset to zero
      PotState = map(analogRead(PotPin), 0, 1024, 0, 255); // Read PotState again so we can exit the loop if it changes
      if (PotState != 125) {
        digitalWrite(RedLEDpin, LEDstate);    // Blink all LEDs so user knows there is an issue
        digitalWrite(GreenLEDpin, LEDstate);
        digitalWrite(PWRLEDpin, LEDstate);
        delay(250);
        LEDstate = !LEDstate;
      }
      else if (PotState == 125) {
        Serial.println("Motion Allowed");
        Serial.println("");
        digitalWrite(RedLEDpin, LOW);
        digitalWrite(GreenLEDpin, LOW);
        digitalWrite(Right_InputA_Pin, LOW);  // Pull Inhibit pin low to allow motion
        digitalWrite(Left_InputA_Pin, LOW);
        EstopSafetyDisable = 0;
      }
    }
  }


  if (LeftHighTime != PrevousLeftHighTime) {
    LeftDutyCycle = ((1 - (LeftHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of precision so we get more precision
    //Serial.print('L');
    //Serial.println(LeftDutyCycle);
    PrevousLeftHighTime = LeftHighTime;
  }

  if (RightHighTime != PrevousRightHighTime) {
    RightDutyCycle = ((1 - (RightHighTime / 22176)) * 1000) - 50;//*1000 instead of 100 because float only has 2 decimals of precision so we get more precision
    //Serial.print('R');
    //Serial.println(RightDutyCycle);
    PrevousRightHighTime = RightHighTime;
  }

  if (TriggerISR == 1 && digitalRead(TriggerOnPin) == 0 && digitalRead(TriggerOffPin) == 1 && TriggerMode == 0) {
    Serial.println("Trigger");
    StartMillis = millis(); // Initial Time used in motor timing loop
    digitalWrite(GreenLEDpin, HIGH);
    TriggerMode = 1;
    TriggerISR = 0;
    EIFR = bit (INT5);  //  Clears ISR Flag, needed because otherwise ISR will trigger again once reenabled, INT5 is the address for pin 3 ISR
    attachInterrupt(digitalPinToInterrupt(TriggerOnPin), Trigger_ISR, FALLING);
  }

  switch (OperatingMode) {
    case 1:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1) {
        Mode1();
      }
      break;
    case 2:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1) {
        Mode2();
      }
      break;
    case 3:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1) {
        Mode3();
      }
      break;
    case 4:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1) {
        Mode4();
      }
      break;
    case 5:
      if (TriggerMode == 0) {
        digitalWrite(Right_Enable_Pin, HIGH);
        digitalWrite(Left_Enable_Pin, HIGH);
        //MotorSpeed = LeftSpeedPWM [0];
        analogWrite(Right_InputB_Pin, RightSpeedPWM [0]);
        analogWrite(Left_InputB_Pin, LeftSpeedPWM [0]);
      }
      else if (TriggerMode == 1) {
        Mode5();
      }
      break;
  }

}

/*
  void Mode1 () {
  if (currentMillis - StartMillis >  0 && currentMillis - StartMillis <= 1000 && stage != 1) {
    //Serial.println("Stage 1");
    MotorSpeed = 20;
    Serial.println("LCCW");
    Serial.println("RCCW");
    digitalWrite(Right_Enable_Pin, HIGH);
    digitalWrite(Left_Enable_Pin, HIGH);
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    stage = 1;
  }
  else if (currentMillis - StartMillis >  1000 && currentMillis - StartMillis <=  2000 && stage != 2) {
    //Serial.println("Stage 2");
    MotorSpeed = 254;
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    Serial.println("LCW");
    Serial.println("RCW");
    stage = 2;
  }
  else if (currentMillis - StartMillis > 2000 && currentMillis - StartMillis <=  3000 && stage != 3) {
    //Serial.println("Stage 3");
    MotorSpeed = 1;
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    Serial.println("LCCW");
    Serial.println("RCCW");
    stage = 3;
  }
  else if (currentMillis - StartMillis > 3000 && currentMillis - StartMillis <=  4000 && stage != 4) {
    //Serial.println("Stage 4");
    MotorSpeed = 128;
    analogWrite(Right_InputB_Pin, MotorSpeed);
    analogWrite(Left_InputB_Pin, MotorSpeed);
    Serial.println("LCW");
    Serial.println("RCW");
    stage = 4;
  }
  else if (currentMillis - StartMillis > 4000 && currentMillis - StartMillis <=  5000 && stage != 5) {
    digitalWrite(Right_InputA_Pin, HIGH);
    digitalWrite(Left_InputA_Pin, HIGH);
    stage = 5;
  }
  else if (currentMillis - StartMillis > 5000 && stage != 6) {
    StartMillis = currentMillis;
    Serial.println("Done");
    digitalWrite(GreenLEDpin, LOW);
    digitalWrite(Right_Enable_Pin, LOW);
    digitalWrite(Right_InputA_Pin, LOW);
    digitalWrite(Right_InputB_Pin, LOW);
    digitalWrite(Left_Enable_Pin, LOW);
    digitalWrite(Left_InputA_Pin, LOW);
    digitalWrite(Left_InputB_Pin, LOW);
    stage = 6;
    TriggerMode = 0;

  }

  }
*/

void Mode1() {
  MotorController(NumSpaces, LeftSpeedPWM, LeftTiming, RightSpeedPWM, RightTiming);
}

void Mode2() {
  MotorController(NumSpaces2, TestSpeed2L, TestTiming2, TestSpeed2R, TestTiming2);
}

void Mode3() {
  MotorController(NumSpaces3, TestSpeed3L, TestTiming3, TestSpeed3R, TestTiming3);
}

void Mode4() {
  MotorController(NumSpaces, LeftSpeedPWM, LeftTiming, RightSpeedPWM, RightTiming);
}

void Mode5() {
  MotorController(NumSpaces5, TestSpeed5L, TestTiming5, TestSpeed5R, TestTiming5);
}

/*
  void Mode5() {
  while (i != 1) {
    for (int j = 0; j < 4; j++) {
      //Serial.println(j);
      Serial.println(LeftSpeedProfile4[j]);
      if (j == 3) {
        Serial.println("Done");
        i = 1;
      }
    }
  }
  while (ReadBeltSpeed != 1 && i == 1) {
    if (Serial.available()) {
      for (int j = 0; j < 4; j++) {
        int IncomingData = Serial.parseInt();
        NewBeltSpeed[j] = IncomingData;
        //Serial.println("Test");
        if (j == 3) {
          for (int k = 0; k < 4; k++) {
            Serial.println(NewBeltSpeed[k]);
            ReadBeltSpeed = 1;
          }
        }
      }
    }
  }
  }
*/

void MotorController (int NumSpaces, int LeftSpeedPWM[], int LeftTiming [], int RightSpeedPWM [], int RightTiming []) {

  if (currentMillis - StartMillis >  0 && currentMillis - StartMillis <= LeftTiming[1] && LeftStage < 1) {
    digitalWrite(Left_Enable_Pin, HIGH);
    analogWrite(Left_InputB_Pin, LeftSpeedPWM [LeftStage]);
    Serial.print("Left Stage ");
    Serial.print(LeftStage);
    Serial.print(" - ");
    Serial.println(LeftSpeedPWM [LeftStage]);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    LeftStage = 1;
  }

  else if (currentMillis - StartMillis >  LeftTiming[LeftStage] && currentMillis - StartMillis <= LeftTiming[LeftStage + 1] && LeftStage >= 1) {
    analogWrite(Left_InputB_Pin, LeftSpeedPWM [LeftStage]);
    //LeftStage=2;
    Serial.print("Left Stage ");
    Serial.print(LeftStage);
    Serial.print(" - ");
    Serial.print(LeftSpeedPWM [LeftStage]);
    Serial.print(", NumSpaces = ");
    Serial.println(NumSpaces);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    LeftStage++;
  }
  else if (LeftStage == NumSpaces - 1) {
    if (LeftTiming[NumSpaces] >= RightTiming[NumSpaces]) {
      Serial.println("Done");
      Serial.println(LeftTiming[NumSpaces - 2]);
      Serial.println(RightTiming[NumSpaces - 2]);
      TriggerMode = 0;
      digitalWrite(GreenLEDpin, LOW);
    }
    LeftStage = 0;
    Serial.println("Left Done");
  }

  // Same for right motor
  if (currentMillis - StartMillis >  0 && currentMillis - StartMillis <= RightTiming[1] && RightStage < 1) {
    digitalWrite(Right_Enable_Pin, HIGH);
    analogWrite(Right_InputB_Pin, RightSpeedPWM [RightStage]);
    Serial.print("Right Stage ");
    Serial.print(RightStage);
    Serial.print(" - ");
    Serial.print(RightSpeedPWM [RightStage]);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    RightStage = 1;
  }

  else if (currentMillis - StartMillis >  RightTiming[RightStage] && currentMillis - StartMillis <= RightTiming[RightStage + 1] && RightStage >= 1) {
    analogWrite(Right_InputB_Pin, RightSpeedPWM [RightStage]);
    //LeftStage=2;
    Serial.print("Right Stage ");
    Serial.print(RightStage);
    Serial.print(" - ");
    Serial.print(RightSpeedPWM [RightStage]);
    Serial.print(", NumSpaces = ");
    Serial.println(NumSpaces);
    //MotorDirection(LeftSpeedPWM[LeftStage], RightSpeedPWM[RightStage]);
    Serial.println();
    RightStage++;
  }
  else if (RightStage == NumSpaces - 1) {
    if (RightTiming[NumSpaces] >= LeftTiming[NumSpaces]) {

      Serial.println(RightTiming[NumSpaces - 1]);
      Serial.println(LeftTiming[NumSpaces - 1]);
      TriggerMode = 0;
      digitalWrite(GreenLEDpin, LOW);
    }
    RightStage = 0;
    Serial.println("Right Done");
  }
}
void MotorDirection (int LeftSpeedPWM, int RightSpeedPWM) {
  if (LeftSpeedPWM < 127) {
    Serial.println("LCCW");
  }
  else if (LeftSpeedPWM > 127) {
    Serial.println("LCW");
  }
  if (RightSpeedPWM < 127) {
    Serial.println("RCCW");
  }
  else if (RightSpeedPWM > 127) {
    Serial.println("RCW");
  }
}


void PerturbationProfile (float WalkingSpeed, int BeltAccel, float dT) {
  // Function to calculate the belt speed profile from the given inputs and
  // convert that to a PWM value, this function assumes 40 data points per second.

  Serial.println("ProfileBegin");

  // Declare Local Varriables
  float r = 0.0762;             // Radius of the hub (m)
  float BeltThickness = 0.0028; // Thickness of the belt (m)
  int GearRto = 5;            // Gear reduction from the motor to the hub
  int TempBeltAccel;          // Store local versioin of BeltAccel so we can midufy it
  int TempAslow;              // Store local version of aSlow so we can modify it
  //int aSlow = -1;              // Rate to slow down the belt after hitting peak speed (m/s^2)

  if (OperatingMode == 5 || OperatingMode == 3 || OperatingMode == 2) {
    //for (int i = 0; i < 331; i++) {
    //LeftTiming[i] = TestTiming5[i];
    //RightTiming[i] = TestTiming5[i];
    //LeftSpeedPWM[i] = TestSpeed5[i];
    //RightSpeedPWM[i] = map(TestSpeed5[i], 1, 254, 254, 1);
    //Serial.print("Timing = ");
    //Serial.println(LeftTiming[i]);
    //Serial.println(LeftSpeedPWM[i]);
    //Serial.println(RightSpeedPWM[i]);

    //}
    goto TheEnd;
  }


  float rNet = r + BeltThickness;

  if (WalkingSpeed >= 0) {
    TempBeltAccel = BeltAccel * (-1);
    TempAslow = aSlow * (-1);
  }
  else if (WalkingSpeed < 0) {
    TempBeltAccel = BeltAccel;
    TempAslow = aSlow;
  }

  Serial.print("dT = ");
  Serial.println(dT);
  Serial.print("BeltAccel = ");
  Serial.println(TempBeltAccel);
  Serial.print("aSlow = ");
  Serial.println(TempAslow);

  // Calculate peak velocity
  //float vf = Vmax;
  float vf = WalkingSpeed + TempBeltAccel * dT;
  Serial.print("vf = ");
  Serial.println(vf);

  // Calculate time to return to Steady State Speed from peak velocity

  float dtSlow = abs((WalkingSpeed - vf) / TempAslow);
  Serial.print("dtSlow = ");
  Serial.println(dtSlow);


  // Calculate angular accel of motor from belt acceleration
  // This is the output tp put into Clearpath's Max Accel
  // Rounded up to nearest intiger
  // Output is in units of RPM/s
  int MotorAngAccel = ceil((TempBeltAccel / r) * (60 / (2 * 3.14)) * GearRto);
  Serial.print("MotorAngAccel = ");
  Serial.println(MotorAngAccel);

  // Save Time and Velocity points in array
  float t[3] = {0, dT * 1000, dT * 1000 + dtSlow * 1000};
  float v[3] = {WalkingSpeed, vf, WalkingSpeed};

  // Create array of timing values
  //Serial.println("numSpacesBegin");
  NumSpaces = (dT + dtSlow) * 40;
  Serial.print("NumSpaces = ");
  Serial.println(NumSpaces);


  //float MotorTiming[NumSpaces];
  float TimingDivision = ((dT + dtSlow) / (NumSpaces - 1)) * 1000;
  Serial.print("TimingDivision = ");
  Serial.println(TimingDivision);

  float TimingSum = 0;
  //float MotorVel[NumSpaces];
  float yIntercept = vf - ((float)TempAslow * dT);
  Serial.print("yIntercept = ");
  Serial.println(yIntercept);
  //float MotorRPM[NumSpaces];
  //byte MotorPWM[NumSpaces];


  for (int i = 0; i < NumSpaces; i++) {
    Serial.println(NumSpaces);
    MotorTiming[i] = round(TimingSum);
    LeftTiming[i] = MotorTiming[i];
    RightTiming[i] = MotorTiming[i];
    //Serial.print("LeftMotorTiming [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(LeftTiming[i]);

    TimingSum = TimingSum + TimingDivision;
    if (MotorTiming[i] <= dT * 1000) {
      MotorVel[i] = TempBeltAccel * ((float)MotorTiming[i] / 1000) + WalkingSpeed;
      //Serial.print("Motor Vel [");
      //Serial.print(i);
      //Serial.print("] =  ");
      //Serial.println(MotorVel);
    }
    else if (MotorTiming[i] > dT * 1000) {
      MotorVel[i] = TempAslow * ((float)MotorTiming[i] / 1000) + yIntercept;
      //Serial.print("Motor Vel [");
      //Serial.print(i);
      //Serial.print("] =  ");
      //Serial.println(MotorVel);
    }

    //MotorRPM[i] = (MotorVel[i]/rNet)*(60/(2*3.1415))*GearRto;
    MotorRPM[i] = (MotorVel[i] / rNet) * (9.549297) * GearRto;
    //Serial.print("MotorRPM [");
    //Serial.print(i);
    //Serial.print("] =  ");
    //Serial.println(MotorRPM[i]);



    // add in a variable for min and max motor speeds because it depends on motor voltage
    float TempPWM;
    //(MotorRPM[i] - -MaxMotorRPM) * (254 - 1) / (2 * MaxMotorRPM) + 1;
    TempPWM = round((MotorRPM[i] + MaxMotorRPM) * 253 / (2 * MaxMotorRPM) + 1);
    //Serial.print("TempPWM = ");
    //Serial.println(TempPWM);

    if (TempPWM > 254) {
      MotorPWM[i] = 254;
    }
    else if (TempPWM < 1) {
      MotorPWM[i] = 1;
    }
    else {
      MotorPWM[i] = TempPWM;
    }

    //Serial.print("MotorPWM = ");
    //Serial.println(MotorPWM);

    //Serial.print("Select State = ");
    //Serial.println(SelectState);
    switch (SelectState) {
      case 1:
        //("Left");
        LeftSpeedPWM[i] = MotorPWM[i];
        //map(value, fromLow, fromHigh, toLow, toHigh)
        RightSpeedPWM[i] = map(MotorPWM[0], 1, 254, 254, 1);
        //RightSpeedPWM[i] = map(MotorPWM[0], 1, 254, 254, 1);
        break;
      case 2:
        //("Right");
        RightSpeedPWM[i] = map(MotorPWM[i], 1, 254, 254, 1);
        //RightSpeedPWM[i] = map(MotorPWM[i], 1, 254, 254, 1);
        LeftSpeedPWM[i] = MotorPWM[0];
        //LeftSpeedPWM[i] = MotorPWM[0];
        break;
      case 3:
        //("BOTH");
        LeftSpeedPWM[i] = MotorPWM[i];
        //Serial.print("First Left PWM [");
        //Serial.print(i);
        //Serial.print("] =  ");
        //Serial.println(LeftSpeedPWM[i]);
        RightSpeedPWM[i] = map(MotorPWM[i], 1, 254, 254, 1);
        break;
    }

    //LeftSpeedPWM[i] = MotorPWM[i];

    Serial.print("Left PWM [");
    Serial.print(i);
    Serial.print("] =  ");
    Serial.println(LeftSpeedPWM[i]);

    Serial.print("Right PWM [");
    Serial.print(i);
    Serial.print("] =  ");
    Serial.println(RightSpeedPWM[i]);
  }
TheEnd:
  Serial.println("PROFILE END");
  Serial.println("");

  //*MotorPWM = &LeftSpeedProfile4
  //*MotorTiming = &LeftMotorTiming4
}


/*
  // ISR to read pwm values sent from motor
  void Left_PWM_Rising () {
  attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), PWM_A_Falling, FALLING);
  //LeftPeriodTime = micros() - LeftRiseTime;
  LeftRiseTime = micros();
  }

  void PWM_A_Falling () {
  attachInterrupt(digitalPinToInterrupt(Left_HLFB_Pin), Left_PWM_Rising, RISING);
  LeftHighTime = micros() - LeftRiseTime;
  }

  void Right_PWM_Rising () {
  attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), PWM_B_Falling, FALLING);
  //RightPeriodTime = micros() - RightRiseTime;
  RightRiseTime = micros();
  }

  void PWM_B_Falling () {
  attachInterrupt(digitalPinToInterrupt(Right_HLFB_Pin), Right_PWM_Rising, RISING);
  RightHighTime = micros() - RightRiseTime;
  }

*/

void Trigger_ISR () {
  detachInterrupt(digitalPinToInterrupt(TriggerOnPin));
  TriggerISR = 1;
  //Serial.println("ISR");
  //Serial.println(digitalRead(TriggerOffPin));
  //Serial.println(digitalRead(TriggerOnPin));
  //TriggerDebounceStart = millis();
}
