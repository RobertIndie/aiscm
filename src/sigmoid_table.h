#define USE_CODE_MEM 0  //静态工作模式请选择为1

#if USE_CODE_MEM
#define CODE code
#else
#define CODE
#endif

#define DEFINE_SIGMOID_TABLE(size) CODE float sigmoid_table[size] =

#ifndef SIGMOID_PRECISION
#define SIGMOID_PRECISION 100
#endif
#if SIGMOID_PRECISION == 100
DEFINE_SIGMOID_TABLE(100){
    0.2689414, 0.2728918, 0.2768782, 0.2809004, 0.2849579, 0.2890505, 0.2931778,
    0.2973393, 0.3015348, 0.3057637, 0.3100255, 0.3143199, 0.3186463, 0.3230041,
    0.327393,  0.3318122, 0.3362613, 0.3407396, 0.3452466, 0.3497815, 0.3543437,
    0.3589326, 0.3635475, 0.3681876, 0.3728522, 0.3775407, 0.3822521, 0.3869858,
    0.391741,  0.3965167, 0.4013123, 0.4061269, 0.4109596, 0.4158095, 0.4206758,
    0.4255575, 0.4304538, 0.4353637, 0.4402863, 0.4452208, 0.450166,  0.4551211,
    0.4600851, 0.465057,  0.4700359, 0.4750208, 0.4800107, 0.4850045, 0.4900013,
    0.4950002, 0.5,       0.5049998, 0.5099987, 0.5149955, 0.5199894, 0.5249792,
    0.529964,  0.5349429, 0.5399149, 0.5448789, 0.549834,  0.5547792, 0.5597137,
    0.5646363, 0.5695462, 0.5744425, 0.5793242, 0.5841905, 0.5890405, 0.5938731,
    0.5986876, 0.6034833, 0.608259,  0.6130142, 0.6177478, 0.6224594, 0.6271477,
    0.6318125, 0.6364526, 0.6410674, 0.6456563, 0.6502185, 0.6547534, 0.6592604,
    0.6637387, 0.6681878, 0.672607,  0.6769959, 0.6813537, 0.6856801, 0.6899745,
    0.6942363, 0.6984652, 0.7026607, 0.7068222, 0.7109495, 0.7150421, 0.7190996,
    0.7231218, 0.7271082,
};
#elif SIGMOID_PRECISION == 500
DEFINE_SIGMOID_TABLE(500){
    0.2689414, 0.2697286, 0.2705172, 0.2713073, 0.2720988, 0.2728918, 0.2736862,
    0.274482,  0.2752793, 0.276078,  0.2768782, 0.2776798, 0.2784828, 0.2792872,
    0.2800931, 0.2809004, 0.281709,  0.2825191, 0.2833306, 0.2841436, 0.2849579,
    0.2857736, 0.2865908, 0.2874093, 0.2882292, 0.2890505, 0.2898732, 0.2906973,
    0.2915227, 0.2923495, 0.2931778, 0.2940074, 0.2948383, 0.2956706, 0.2965043,
    0.2973393, 0.2981758, 0.2990135, 0.2998526, 0.300693,  0.3015348, 0.3023779,
    0.3032224, 0.3040681, 0.3049152, 0.3057637, 0.3066134, 0.3074645, 0.3083168,
    0.3091705, 0.3100255, 0.3108818, 0.3117394, 0.3125983, 0.3134584, 0.3143199,
    0.3151826, 0.3160466, 0.3169119, 0.3177784, 0.3186463, 0.3195153, 0.3203857,
    0.3212572, 0.3221301, 0.3230041, 0.3238795, 0.324756,  0.3256338, 0.3265128,
    0.327393,  0.3282744, 0.3291571, 0.3300409, 0.330926,  0.3318122, 0.3326997,
    0.3335883, 0.3344781, 0.3353691, 0.3362613, 0.3371547, 0.3380491, 0.3389448,
    0.3398416, 0.3407396, 0.3416387, 0.342539,  0.3434404, 0.3443429, 0.3452466,
    0.3461513, 0.3470572, 0.3479642, 0.3488722, 0.3497815, 0.3506917, 0.3516031,
    0.3525155, 0.3534291, 0.3543437, 0.3552594, 0.3561761, 0.3570939, 0.3580127,
    0.3589326, 0.3598535, 0.3607754, 0.3616984, 0.3626224, 0.3635475, 0.3644735,
    0.3654005, 0.3663285, 0.3672576, 0.3681876, 0.3691186, 0.3700505, 0.3709835,
    0.3719174, 0.3728522, 0.3737881, 0.3747248, 0.3756625, 0.3766011, 0.3775407,
    0.3784811, 0.3794225, 0.3803648, 0.381308,  0.3822521, 0.3831971, 0.384143,
    0.3850897, 0.3860373, 0.3869858, 0.3879352, 0.3888853, 0.3898364, 0.3907883,
    0.391741,  0.3926945, 0.3936488, 0.394604,  0.39556,   0.3965167, 0.3974743,
    0.3984327, 0.3993918, 0.4003517, 0.4013123, 0.4022738, 0.4032359, 0.4041989,
    0.4051625, 0.4061269, 0.407092,  0.4080578, 0.4090244, 0.4099916, 0.4109596,
    0.4119282, 0.4128975, 0.4138675, 0.4148382, 0.4158095, 0.4167815, 0.4177541,
    0.4187273, 0.4197012, 0.4206758, 0.4216509, 0.4226266, 0.423603,  0.4245799,
    0.4255575, 0.4265356, 0.4275143, 0.4284936, 0.4294734, 0.4304538, 0.4314347,
    0.4324162, 0.4333982, 0.4343807, 0.4353637, 0.4363472, 0.4373313, 0.4383158,
    0.4393009, 0.4402863, 0.4412723, 0.4422587, 0.4432456, 0.444233,  0.4452208,
    0.446209,  0.4471976, 0.4481867, 0.4491761, 0.450166,  0.4511563, 0.4521469,
    0.453138,  0.4541293, 0.4551211, 0.4561132, 0.4571057, 0.4580985, 0.4590917,
    0.4600851, 0.4610789, 0.462073,  0.4630674, 0.4640621, 0.465057,  0.4660523,
    0.4670478, 0.4680436, 0.4690397, 0.4700359, 0.4710325, 0.4720292, 0.4730262,
    0.4740234, 0.4750208, 0.4760184, 0.4770162, 0.4780142, 0.4790123, 0.4800107,
    0.4810092, 0.4820078, 0.4830065, 0.4840055, 0.4850045, 0.4860037, 0.4870029,
    0.4880023, 0.4890018, 0.4900013, 0.491001,  0.4920007, 0.4930005, 0.4940003,
    0.4950002, 0.4960001, 0.497,     0.498,     0.499,     0.5,       0.501,
    0.502,     0.503,     0.5039999, 0.5049998, 0.5059997, 0.5069996, 0.5079993,
    0.508999,  0.5099987, 0.5109982, 0.5119977, 0.5129971, 0.5139964, 0.5149955,
    0.5159945, 0.5169935, 0.5179922, 0.5189909, 0.5199894, 0.5209876, 0.5219858,
    0.5229838, 0.5239816, 0.5249792, 0.5259766, 0.5269738, 0.5279707, 0.5289675,
    0.529964,  0.5309603, 0.5319564, 0.5329522, 0.5339477, 0.5349429, 0.5359379,
    0.5369326, 0.537927,  0.5389211, 0.5399149, 0.5409083, 0.5419015, 0.5428943,
    0.5438868, 0.5448789, 0.5458707, 0.5468621, 0.5478531, 0.5488437, 0.549834,
    0.5508239, 0.5518133, 0.5528024, 0.553791,  0.5547792, 0.555767,  0.5567544,
    0.5577412, 0.5587277, 0.5597137, 0.5606992, 0.5616842, 0.5626687, 0.5636528,
    0.5646363, 0.5656193, 0.5666019, 0.5675839, 0.5685653, 0.5695462, 0.5705266,
    0.5715064, 0.5724857, 0.5734644, 0.5744425, 0.5754201, 0.576397,  0.5773734,
    0.5783491, 0.5793242, 0.5802988, 0.5812727, 0.5822459, 0.5832186, 0.5841905,
    0.5851619, 0.5861325, 0.5871025, 0.5880718, 0.5890405, 0.5900084, 0.5909756,
    0.5919421, 0.592908,  0.5938731, 0.5948375, 0.5958012, 0.5967641, 0.5977262,
    0.5986876, 0.5996484, 0.6006082, 0.6015673, 0.6025257, 0.6034833, 0.60444,
    0.605396,  0.6063511, 0.6073055, 0.608259,  0.6092117, 0.6101636, 0.6111147,
    0.6120648, 0.6130142, 0.6139627, 0.6149102, 0.615857,  0.6168029, 0.6177478,
    0.618692,  0.6196352, 0.6205775, 0.6215189, 0.6224594, 0.6233989, 0.6243375,
    0.6252752, 0.6262119, 0.6271477, 0.6280826, 0.6290165, 0.6299495, 0.6308814,
    0.6318125, 0.6327424, 0.6336715, 0.6345994, 0.6355265, 0.6364526, 0.6373776,
    0.6383016, 0.6392245, 0.6401465, 0.6410674, 0.6419873, 0.6429061, 0.6438239,
    0.6447406, 0.6456563, 0.6465709, 0.6474844, 0.6483969, 0.6493083, 0.6502185,
    0.6511278, 0.6520358, 0.6529428, 0.6538487, 0.6547534, 0.6556571, 0.6565596,
    0.657461,  0.6583613, 0.6592604, 0.6601583, 0.6610551, 0.6619509, 0.6628454,
    0.6637387, 0.6646309, 0.6655219, 0.6664117, 0.6673003, 0.6681878, 0.6690741,
    0.6699591, 0.6708429, 0.6717256, 0.672607,  0.6734872, 0.6743662, 0.675244,
    0.6761205, 0.6769959, 0.6778699, 0.6787428, 0.6796143, 0.6804847, 0.6813537,
    0.6822215, 0.6830881, 0.6839534, 0.6848174, 0.6856801, 0.6865416, 0.6874017,
    0.6882606, 0.6891182, 0.6899745, 0.6908295, 0.6916832, 0.6925355, 0.6933866,
    0.6942363, 0.6950848, 0.6959319, 0.6967776, 0.6976221, 0.6984652, 0.699307,
    0.7001474, 0.7009865, 0.7018242, 0.7026607, 0.7034957, 0.7043294, 0.7051617,
    0.7059926, 0.7068222, 0.7076504, 0.7084773, 0.7093027, 0.7101268, 0.7109495,
    0.7117708, 0.7125907, 0.7134092, 0.7142264, 0.7150421, 0.7158564, 0.7166693,
    0.7174808, 0.718291,  0.7190996, 0.7199069, 0.7207128, 0.7215172, 0.7223202,
    0.7231218, 0.723922,  0.7247207, 0.7255179, 0.7263138, 0.7271082, 0.7279012,
    0.7286927, 0.7294828, 0.7302714,
};
#elif SIGMOID_PRECISION 1000
DEFINE_SIGMOID_TABLE(1000){
    0.2689414, 0.2693348, 0.2697286, 0.2701227, 0.2705172, 0.2709121, 0.2713073,
    0.2717029, 0.2720988, 0.2724951, 0.2728918, 0.2732888, 0.2736862, 0.2740839,
    0.274482,  0.2748805, 0.2752793, 0.2756785, 0.276078,  0.2764779, 0.2768782,
    0.2772788, 0.2776798, 0.2780811, 0.2784828, 0.2788848, 0.2792872, 0.27969,
    0.2800931, 0.2804965, 0.2809004, 0.2813045, 0.281709,  0.2821139, 0.2825191,
    0.2829247, 0.2833306, 0.2837369, 0.2841436, 0.2845505, 0.2849579, 0.2853656,
    0.2857736, 0.286182,  0.2865908, 0.2869998, 0.2874093, 0.2878191, 0.2882292,
    0.2886397, 0.2890505, 0.2894617, 0.2898732, 0.2902851, 0.2906973, 0.2911098,
    0.2915227, 0.291936,  0.2923495, 0.2927635, 0.2931778, 0.2935924, 0.2940074,
    0.2944227, 0.2948383, 0.2952543, 0.2956706, 0.2960873, 0.2965043, 0.2969216,
    0.2973393, 0.2977574, 0.2981758, 0.2985944, 0.2990135, 0.2994329, 0.2998526,
    0.3002726, 0.300693,  0.3011137, 0.3015348, 0.3019562, 0.3023779, 0.3028,
    0.3032224, 0.3036451, 0.3040681, 0.3044915, 0.3049152, 0.3053393, 0.3057637,
    0.3061884, 0.3066134, 0.3070388, 0.3074645, 0.3078905, 0.3083168, 0.3087435,
    0.3091705, 0.3095978, 0.3100255, 0.3104535, 0.3108818, 0.3113104, 0.3117394,
    0.3121687, 0.3125983, 0.3130282, 0.3134584, 0.313889,  0.3143199, 0.3147511,
    0.3151826, 0.3156145, 0.3160466, 0.3164791, 0.3169119, 0.317345,  0.3177784,
    0.3182122, 0.3186463, 0.3190807, 0.3195153, 0.3199503, 0.3203857, 0.3208213,
    0.3212572, 0.3216935, 0.3221301, 0.322567,  0.3230041, 0.3234417, 0.3238795,
    0.3243176, 0.324756,  0.3251947, 0.3256338, 0.3260731, 0.3265128, 0.3269527,
    0.327393,  0.3278335, 0.3282744, 0.3287156, 0.3291571, 0.3295988, 0.3300409,
    0.3304833, 0.330926,  0.331369,  0.3318122, 0.3322558, 0.3326997, 0.3331439,
    0.3335883, 0.3340331, 0.3344781, 0.3349235, 0.3353691, 0.3358151, 0.3362613,
    0.3367078, 0.3371547, 0.3376018, 0.3380491, 0.3384968, 0.3389448, 0.3393931,
    0.3398416, 0.3402905, 0.3407396, 0.341189,  0.3416387, 0.3420887, 0.342539,
    0.3429895, 0.3434404, 0.3438915, 0.3443429, 0.3447946, 0.3452466, 0.3456988,
    0.3461513, 0.3466041, 0.3470572, 0.3475105, 0.3479642, 0.3484181, 0.3488722,
    0.3493267, 0.3497815, 0.3502364, 0.3506917, 0.3511473, 0.3516031, 0.3520592,
    0.3525155, 0.3529722, 0.3534291, 0.3538862, 0.3543437, 0.3548014, 0.3552594,
    0.3557176, 0.3561761, 0.3566349, 0.3570939, 0.3575532, 0.3580127, 0.3584725,
    0.3589326, 0.3593929, 0.3598535, 0.3603144, 0.3607754, 0.3612368, 0.3616984,
    0.3621603, 0.3626224, 0.3630848, 0.3635475, 0.3640103, 0.3644735, 0.3649369,
    0.3654005, 0.3658644, 0.3663285, 0.3667929, 0.3672576, 0.3677225, 0.3681876,
    0.3686529, 0.3691186, 0.3695844, 0.3700505, 0.3705169, 0.3709835, 0.3714503,
    0.3719174, 0.3723847, 0.3728522, 0.37332,   0.3737881, 0.3742563, 0.3747248,
    0.3751935, 0.3756625, 0.3761317, 0.3766011, 0.3770708, 0.3775407, 0.3780108,
    0.3784811, 0.3789517, 0.3794225, 0.3798936, 0.3803648, 0.3808363, 0.381308,
    0.38178,   0.3822521, 0.3827245, 0.3831971, 0.3836699, 0.384143,  0.3846163,
    0.3850897, 0.3855634, 0.3860373, 0.3865115, 0.3869858, 0.3874604, 0.3879352,
    0.3884102, 0.3888853, 0.3893608, 0.3898364, 0.3903122, 0.3907883, 0.3912645,
    0.391741,  0.3922176, 0.3926945, 0.3931716, 0.3936488, 0.3941263, 0.394604,
    0.3950819, 0.39556,   0.3960383, 0.3965167, 0.3969954, 0.3974743, 0.3979534,
    0.3984327, 0.3989121, 0.3993918, 0.3998716, 0.4003517, 0.4008319, 0.4013123,
    0.4017929, 0.4022738, 0.4027548, 0.4032359, 0.4037173, 0.4041989, 0.4046806,
    0.4051625, 0.4056446, 0.4061269, 0.4066094, 0.407092,  0.4075748, 0.4080578,
    0.408541,  0.4090244, 0.4095079, 0.4099916, 0.4104755, 0.4109596, 0.4114438,
    0.4119282, 0.4124128, 0.4128975, 0.4133824, 0.4138675, 0.4143527, 0.4148382,
    0.4153237, 0.4158095, 0.4162954, 0.4167815, 0.4172677, 0.4177541, 0.4182406,
    0.4187273, 0.4192142, 0.4197012, 0.4201884, 0.4206758, 0.4211632, 0.4216509,
    0.4221387, 0.4226266, 0.4231147, 0.423603,  0.4240914, 0.4245799, 0.4250686,
    0.4255575, 0.4260465, 0.4265356, 0.4270249, 0.4275143, 0.4280039, 0.4284936,
    0.4289834, 0.4294734, 0.4299635, 0.4304538, 0.4309442, 0.4314347, 0.4319254,
    0.4324162, 0.4329071, 0.4333982, 0.4338894, 0.4343807, 0.4348721, 0.4353637,
    0.4358554, 0.4363472, 0.4368392, 0.4373313, 0.4378235, 0.4383158, 0.4388083,
    0.4393009, 0.4397936, 0.4402863, 0.4407793, 0.4412723, 0.4417655, 0.4422587,
    0.4427522, 0.4432456, 0.4437393, 0.444233,  0.4447268, 0.4452208, 0.4457148,
    0.446209,  0.4467033, 0.4471976, 0.4476921, 0.4481867, 0.4486814, 0.4491761,
    0.449671,  0.450166,  0.4506611, 0.4511563, 0.4516515, 0.4521469, 0.4526424,
    0.453138,  0.4536336, 0.4541293, 0.4546252, 0.4551211, 0.4556171, 0.4561132,
    0.4566094, 0.4571057, 0.4576021, 0.4580985, 0.458595,  0.4590917, 0.4595883,
    0.4600851, 0.460582,  0.4610789, 0.4615759, 0.462073,  0.4625702, 0.4630674,
    0.4635647, 0.4640621, 0.4645595, 0.465057,  0.4655547, 0.4660523, 0.4665501,
    0.4670478, 0.4675457, 0.4680436, 0.4685416, 0.4690397, 0.4695378, 0.4700359,
    0.4705342, 0.4710325, 0.4715308, 0.4720292, 0.4725277, 0.4730262, 0.4735248,
    0.4740234, 0.4745221, 0.4750208, 0.4755196, 0.4760184, 0.4765173, 0.4770162,
    0.4775152, 0.4780142, 0.4785132, 0.4790123, 0.4795115, 0.4800107, 0.4805099,
    0.4810092, 0.4815084, 0.4820078, 0.4825071, 0.4830065, 0.483506,  0.4840055,
    0.484505,  0.4850045, 0.4855041, 0.4860037, 0.4865033, 0.4870029, 0.4875026,
    0.4880023, 0.488502,  0.4890018, 0.4895015, 0.4900013, 0.4905011, 0.491001,
    0.4915008, 0.4920007, 0.4925006, 0.4930005, 0.4935004, 0.4940003, 0.4945002,
    0.4950002, 0.4955001, 0.4960001, 0.4965001, 0.497,     0.4975,    0.498,
    0.4985,    0.499,     0.4995,    0.5,       0.5005,    0.501,     0.5015,
    0.502,     0.5025,    0.503,     0.5034999, 0.5039999, 0.5044999, 0.5049998,
    0.5054998, 0.5059997, 0.5064996, 0.5069996, 0.5074995, 0.5079993, 0.5084992,
    0.508999,  0.5094988, 0.5099987, 0.5104985, 0.5109982, 0.511498,  0.5119977,
    0.5124974, 0.5129971, 0.5134967, 0.5139964, 0.5144959, 0.5149955, 0.5154951,
    0.5159945, 0.516494,  0.5169935, 0.5174928, 0.5179922, 0.5184916, 0.5189909,
    0.5194901, 0.5199894, 0.5204885, 0.5209876, 0.5214868, 0.5219858, 0.5224848,
    0.5229838, 0.5234827, 0.5239816, 0.5244804, 0.5249792, 0.5254779, 0.5259766,
    0.5264752, 0.5269738, 0.5274723, 0.5279707, 0.5284692, 0.5289675, 0.5294658,
    0.529964,  0.5304622, 0.5309603, 0.5314584, 0.5319564, 0.5324543, 0.5329522,
    0.5334499, 0.5339477, 0.5344453, 0.5349429, 0.5354404, 0.5359379, 0.5364353,
    0.5369326, 0.5374298, 0.537927,  0.5384241, 0.5389211, 0.539418,  0.5399149,
    0.5404117, 0.5409083, 0.541405,  0.5419015, 0.5423979, 0.5428943, 0.5433906,
    0.5438868, 0.5443829, 0.5448789, 0.5453748, 0.5458707, 0.5463664, 0.5468621,
    0.5473576, 0.5478531, 0.5483485, 0.5488437, 0.5493389, 0.549834,  0.550329,
    0.5508239, 0.5513186, 0.5518133, 0.5523079, 0.5528024, 0.5532967, 0.553791,
    0.5542852, 0.5547792, 0.5552732, 0.555767,  0.5562608, 0.5567544, 0.5572479,
    0.5577412, 0.5582345, 0.5587277, 0.5592207, 0.5597137, 0.5602065, 0.5606992,
    0.5611917, 0.5616842, 0.5621765, 0.5626687, 0.5631608, 0.5636528, 0.5641446,
    0.5646363, 0.5651278, 0.5656193, 0.5661107, 0.5666019, 0.5670929, 0.5675839,
    0.5680746, 0.5685653, 0.5690559, 0.5695462, 0.5700365, 0.5705266, 0.5710166,
    0.5715064, 0.5719962, 0.5724857, 0.5729751, 0.5734644, 0.5739535, 0.5744425,
    0.5749313, 0.5754201, 0.5759086, 0.576397,  0.5768853, 0.5773734, 0.5778613,
    0.5783491, 0.5788367, 0.5793242, 0.5798116, 0.5802988, 0.5807858, 0.5812727,
    0.5817594, 0.5822459, 0.5827323, 0.5832186, 0.5837047, 0.5841905, 0.5846763,
    0.5851619, 0.5856472, 0.5861325, 0.5866176, 0.5871025, 0.5875872, 0.5880718,
    0.5885562, 0.5890405, 0.5895245, 0.5900084, 0.5904921, 0.5909756, 0.591459,
    0.5919421, 0.5924252, 0.592908,  0.5933906, 0.5938731, 0.5943554, 0.5948375,
    0.5953194, 0.5958012, 0.5962827, 0.5967641, 0.5972452, 0.5977262, 0.5982071,
    0.5986876, 0.5991681, 0.5996484, 0.6001284, 0.6006082, 0.6010879, 0.6015673,
    0.6020466, 0.6025257, 0.6030046, 0.6034833, 0.6039617, 0.60444,   0.6049181,
    0.605396,  0.6058736, 0.6063511, 0.6068285, 0.6073055, 0.6077824, 0.608259,
    0.6087355, 0.6092117, 0.6096878, 0.6101636, 0.6106392, 0.6111147, 0.6115898,
    0.6120648, 0.6125396, 0.6130142, 0.6134885, 0.6139627, 0.6144366, 0.6149102,
    0.6153837, 0.615857,  0.61633,   0.6168029, 0.6172755, 0.6177478, 0.61822,
    0.618692,  0.6191637, 0.6196352, 0.6201065, 0.6205775, 0.6210483, 0.6215189,
    0.6219892, 0.6224594, 0.6229292, 0.6233989, 0.6238683, 0.6243375, 0.6248065,
    0.6252752, 0.6257437, 0.6262119, 0.62668,   0.6271477, 0.6276153, 0.6280826,
    0.6285497, 0.6290165, 0.6294831, 0.6299495, 0.6304156, 0.6308814, 0.6313471,
    0.6318125, 0.6322775, 0.6327424, 0.6332071, 0.6336715, 0.6341356, 0.6345994,
    0.6350631, 0.6355265, 0.6359897, 0.6364526, 0.6369151, 0.6373776, 0.6378397,
    0.6383016, 0.6387632, 0.6392245, 0.6396856, 0.6401465, 0.6406071, 0.6410674,
    0.6415275, 0.6419873, 0.6424468, 0.6429061, 0.6433651, 0.6438239, 0.6442824,
    0.6447406, 0.6451986, 0.6456563, 0.6461138, 0.6465709, 0.6470278, 0.6474844,
    0.6479408, 0.6483969, 0.6488527, 0.6493083, 0.6497635, 0.6502185, 0.6506733,
    0.6511278, 0.6515819, 0.6520358, 0.6524895, 0.6529428, 0.6533959, 0.6538487,
    0.6543012, 0.6547534, 0.6552054, 0.6556571, 0.6561085, 0.6565596, 0.6570104,
    0.657461,  0.6579113, 0.6583613, 0.658811,  0.6592604, 0.6597095, 0.6601583,
    0.6606069, 0.6610551, 0.6615032, 0.6619509, 0.6623982, 0.6628454, 0.6632922,
    0.6637387, 0.6641849, 0.6646309, 0.6650765, 0.6655219, 0.6659669, 0.6664117,
    0.6668562, 0.6673003, 0.6677442, 0.6681878, 0.6686311, 0.6690741, 0.6695167,
    0.6699591, 0.6704012, 0.6708429, 0.6712844, 0.6717256, 0.6721665, 0.672607,
    0.6730473, 0.6734872, 0.6739269, 0.6743662, 0.6748053, 0.675244,  0.6756824,
    0.6761205, 0.6765584, 0.6769959, 0.6774331, 0.6778699, 0.6783065, 0.6787428,
    0.6791787, 0.6796143, 0.6800497, 0.6804847, 0.6809193, 0.6813537, 0.6817878,
    0.6822215, 0.682655,  0.6830881, 0.6835209, 0.6839534, 0.6843855, 0.6848174,
    0.6852489, 0.6856801, 0.686111,  0.6865416, 0.6869718, 0.6874017, 0.6878313,
    0.6882606, 0.6886896, 0.6891182, 0.6895465, 0.6899745, 0.6904022, 0.6908295,
    0.6912565, 0.6916832, 0.6921095, 0.6925355, 0.6929612, 0.6933866, 0.6938117,
    0.6942363, 0.6946607, 0.6950848, 0.6955085, 0.6959319, 0.6963549, 0.6967776,
    0.6972001, 0.6976221, 0.6980438, 0.6984652, 0.6988863, 0.699307,  0.6997274,
    0.7001474, 0.7005671, 0.7009865, 0.7014055, 0.7018242, 0.7022426, 0.7026607,
    0.7030783, 0.7034957, 0.7039127, 0.7043294, 0.7047457, 0.7051617, 0.7055773,
    0.7059926, 0.7064076, 0.7068222, 0.7072365, 0.7076504, 0.708064,  0.7084773,
    0.7088901, 0.7093027, 0.7097149, 0.7101268, 0.7105383, 0.7109495, 0.7113603,
    0.7117708, 0.7121809, 0.7125907, 0.7130002, 0.7134092, 0.713818,  0.7142264,
    0.7146344, 0.7150421, 0.7154495, 0.7158564, 0.7162631, 0.7166693, 0.7170753,
    0.7174808, 0.7178861, 0.718291,  0.7186955, 0.7190996, 0.7195035, 0.7199069,
    0.72031,   0.7207128, 0.7211152, 0.7215172, 0.7219189, 0.7223202, 0.7227212,
    0.7231218, 0.7235221, 0.723922,  0.7243215, 0.7247207, 0.7251195, 0.7255179,
    0.7259161, 0.7263138, 0.7267112, 0.7271082, 0.7275049, 0.7279012, 0.7282971,
    0.7286927, 0.7290879, 0.7294828, 0.7298773, 0.7302714, 0.7306652,
};
#endif