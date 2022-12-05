#include "l2_minimization.h"

#include <chrono>
#include <fstream>
#include <sstream>

#include <gtest/gtest.h>
#include "caffe2/core/logging.h"

using namespace std;
using namespace dnnlowp;

string default_input[] = {
    // rage includes 0
    "-14.4819 12.6174 1024 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 3 0 0 0 1 1 0 1 0 1 0 0 0 0 3 2 2 2 0 0 2 2 4 0 1 2 2 1 1 0 1 3 1 2 2 3 2 2 2 1 9 9 5 9 17 10 9 8 4 4 4 5 9 7 9 3 12 7 13 10 12 9 4 9 10 14 13 10 12 18 16 15 20 22 18 12 17 23 22 20 18 20 31 20 30 33 31 28 36 29 33 37 28 38 48 51 48 39 46 35 68 55 64 56 79 66 87 82 83 59 82 74 86 70 92 93 97 99 94 92 100 109 130 128 134 153 152 152 163 182 172 186 173 195 182 217 224 208 212 264 254 246 285 290 266 304 315 344 345 409 395 437 437 396 437 493 543 507 551 550 599 581 688 650 689 699 771 747 751 913 891 880 947 942 1068 1060 1110 1096 1167 1208 1251 1312 1316 1370 1458 1501 1522 1588 1799 1728 1839 1864 1920 1969 2140 2208 2277 2472 2618 2594 2647 2695 2906 2968 3213 3236 3345 3472 3593 3833 3827 3985 4139 4446 4565 4782 4990 5311 5375 5654 5734 5942 6318 6462 6698 7072 8541 35660 10040 9865 10676 10353 10335 10696 11168 11734 11929 12437 12902 13332 14075 14308 15099 15868 16618 18694 58761 19945 22434 20671 20621 21792 22358 23578 23604 23934 24927 25666 27543 27018 28804 29380 31421 36359 55743 46541 40062 39360 40569 41932 41835 43952 72601 46669 47467 49251 49964 51811 52562 54314 56716 57971 60032 61913 64570 65761 68703 70787 73202 113303 91403 84575 88611 90390 134000 99299 99505 101272 104403 123506 129581 120189 120348 124118 129191 133399 137058 144731 148338 190935 208894 168230 177385 181398 187614 200232 637370 244761 253000 239661 243444 251450 281095 258096 282346 273498 284072 290493 299562 373466 321624 329935 339275 354175 361193 399737 387712 399316 414993 432027 449814 504634 477803 496667 517560 529784 548026 572150 595161 621153 668268 1237622 749055 791405 757456 776040 799111 853492 883829 883712 936781 945772 998249 1021699 1061104 1393549 1226423 1316189 1423312 1470827 1534637 1589081 1597358 1710996 1848210 2027547 2217233 2350514 2328073 2438732 2474078 2562581 2871633 2922957 3055742 3108723 3262467 4773865 3587091 3735731 4463169 4406105 4679926 4437677 4894005 4786549 5047926 5693089 5655876 5689014 6419603 6151189 6648580 6628528 7337991 7674408 8011681 7932698 7988401 8470319 8646275 9389563 9935716 9660529 9778487 10240827 10293903 11404105 11040799 11469412 11723622 12111508 12526719 12687955 13896509 14154808 13838654 14155982 15109963 14970065 15790522 15886441 16545165 17042598 17931894 18647781 20142964 19898193 20420633 20953720 22252049 22240446 23509713 24513666 24771753 25561492 26461802 27707581 28685197 29378145 29857300 31193241 32246011 33244081 33602678 35140279 35872415 37271884 38311598 39491447 40498747 41698552 43214154 44398181 45924085 46928842 48469275 49572355 52338257 52983303 54521834 55861209 57879978 60114437 61286530 62571720 65115340 67390927 68879548 71046167 72718276 74629636 77557546 80757826 84136551 87339336 92356649 95308835 100486370 104126661 107849598 111205762 115189340 119903792 124273189 128738583 136744605 143611920 154565499 220943249 242922824 213454161 234272651 229962555 213317331 209488838 295957342 211725998 216032281 214691829 431135331 257880768 241686786 216762053 218086136 328985166 220837815 218284596 216312313 214319683 214271325 219030575 222436217 239825320 296573991 235773880 203981045 189446590 185708731 382579729 175940878 172193990 176387589 334884879 208722519 165754706 169503769 200965237 139103476 135561652 289568831 130429746 133279443 156769388 361150135 154462443 183342040 137279919 123747920 114084613 108776361 107283116 105123865 103631484 102435023 100278069 98425803 97120894 94559049 92647136 90617643 88889308 87225160 85852040 84337893 82438175 81405526 78999147 77516179 76386779 74231849 72885367 70746351 69858811 67953055 66765868 65372509 63653388 62411728 61000372 59500529 58341696 57521812 56354581 54386520 53341443 52927384 50630413 49357539 47848548 47018272 46503519 44643259 43497911 42410663 41279647 40192482 39502463 38562766 37773698 35222759 34458680 33876230 32479673 31209766 30365850 29592875 29035457 28367812 27229674 26372275 25898054 25555505 24968412 23753959 23269936 23227518 22695066 21710471 21176955 20601857 20236569 20004844 19319804 18393986 18096955 17296082 17188733 16840513 15670166 15271049 14826521 15357804 14002179 13827443 13126386 12922421 12291672 12597874 11657190 11459238 11581520 10766826 10354715 10252391 10443916 9737638 9953012 8885546 8715375 9021612 9035091 7927433 7759211 7536034 7281256 7644331 6931387 6794666 6974275 6741241 6546644 6224667 5498319 6091985 5104544 4988526 5075334 4333385 4017618 4357278 3985067 3628212 3469888 3366441 3866122 3382820 3063351 3348379 3021319 2391575 2263357 2283341 2263544 2076849 2008142 2374224 1788830 1966099 1688494 1614656 1632424 1543255 1511824 1435361 1360517 1358924 1746468 1690795 1080391 1033566 1456255 905742 880725 932729 1268859 801632 760334 698575 696917 1063164 655091 675535 601858 527519 479684 462317 396671 374043 382168 334811 319494 306304 294786 285515 280022 278821 274855 303220 315830 778544 254790 226584 226892 259248 241107 165469 151197 172888 150515 122063 115610 127487 128926 99212 94380 90918 89276 87128 83774 84592 89458 88584 91447 127156 119073 91345 63001 48500 42958 38095 62191 32412 48868 27593 23637 22308 21392 20799 18845 17980 36035 15808 14964 13455 12667 12075 11213 10559 10228 9604 9374 8718 8067 7793 7378 6964 6600 6393 5991 5810 5405 5156 5016 4798 4604 4333 4259 3978 3923 3677 3583 3259 3084 2958 2874 2706 2522 2470 2471 2270 2227 2050 1874 1964 1856 1784 1722 1575 1540 1445 1461 1358 1225 1211 1164 1072 1088 1013 929 977 924 807 773 819 763 721 681 644 588 597 538 503 481 485 434 419 405 394 376 388 336 364 323 309 313 287 275 225 241 245 212 200 213 168 162 177 149 154 162 175 175 207 115 111 102 88 74 82 85 82 94 73 71 59 56 58 39 36 34 44 47 41 30 36 34 37 34 33 31 31 28 23 25 21 20 27 17 17 14 16 16 14 18 9 8 12 8 11 8 10 11 6 8 5 6 2 4 7 10 5 3 1 3 7 3 1 3 3 6 4 4 1 5 3 4 2 0 1 2 4 0 2 2 1 0 1 2 0 1 1 1 0 1 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
    // min > 0
    "14.4819 22.6175 1024 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 3 0 0 0 1 1 0 1 0 1 0 0 0 0 3 2 2 2 0 0 2 2 4 0 1 2 2 1 1 0 1 3 1 2 2 3 2 2 2 1 9 9 5 9 17 10 9 8 4 4 4 5 9 7 9 3 12 7 13 10 12 9 4 9 10 14 13 10 12 18 16 15 20 22 18 12 17 23 22 20 18 20 31 20 30 33 31 28 36 29 33 37 28 38 48 51 48 39 46 35 68 55 64 56 79 66 87 82 83 59 82 74 86 70 92 93 97 99 94 92 100 109 130 128 134 153 152 152 163 182 172 186 173 195 182 217 224 208 212 264 254 246 285 290 266 304 315 344 345 409 395 437 437 396 437 493 543 507 551 550 599 581 688 650 689 699 771 747 751 913 891 880 947 942 1068 1060 1110 1096 1167 1208 1251 1312 1316 1370 1458 1501 1522 1588 1799 1728 1839 1864 1920 1969 2140 2208 2277 2472 2618 2594 2647 2695 2906 2968 3213 3236 3345 3472 3593 3833 3827 3985 4139 4446 4565 4782 4990 5311 5375 5654 5734 5942 6318 6462 6698 7072 8541 35660 10040 9865 10676 10353 10335 10696 11168 11734 11929 12437 12902 13332 14075 14308 15099 15868 16618 18694 58761 19945 22434 20671 20621 21792 22358 23578 23604 23934 24927 25666 27543 27018 28804 29380 31421 36359 55743 46541 40062 39360 40569 41932 41835 43952 72601 46669 47467 49251 49964 51811 52562 54314 56716 57971 60032 61913 64570 65761 68703 70787 73202 113303 91403 84575 88611 90390 134000 99299 99505 101272 104403 123506 129581 120189 120348 124118 129191 133399 137058 144731 148338 190935 208894 168230 177385 181398 187614 200232 637370 244761 253000 239661 243444 251450 281095 258096 282346 273498 284072 290493 299562 373466 321624 329935 339275 354175 361193 399737 387712 399316 414993 432027 449814 504634 477803 496667 517560 529784 548026 572150 595161 621153 668268 1237622 749055 791405 757456 776040 799111 853492 883829 883712 936781 945772 998249 1021699 1061104 1393549 1226423 1316189 1423312 1470827 1534637 1589081 1597358 1710996 1848210 2027547 2217233 2350514 2328073 2438732 2474078 2562581 2871633 2922957 3055742 3108723 3262467 4773865 3587091 3735731 4463169 4406105 4679926 4437677 4894005 4786549 5047926 5693089 5655876 5689014 6419603 6151189 6648580 6628528 7337991 7674408 8011681 7932698 7988401 8470319 8646275 9389563 9935716 9660529 9778487 10240827 10293903 11404105 11040799 11469412 11723622 12111508 12526719 12687955 13896509 14154808 13838654 14155982 15109963 14970065 15790522 15886441 16545165 17042598 17931894 18647781 20142964 19898193 20420633 20953720 22252049 22240446 23509713 24513666 24771753 25561492 26461802 27707581 28685197 29378145 29857300 31193241 32246011 33244081 33602678 35140279 35872415 37271884 38311598 39491447 40498747 41698552 43214154 44398181 45924085 46928842 48469275 49572355 52338257 52983303 54521834 55861209 57879978 60114437 61286530 62571720 65115340 67390927 68879548 71046167 72718276 74629636 77557546 80757826 84136551 87339336 92356649 95308835 100486370 104126661 107849598 111205762 115189340 119903792 124273189 128738583 136744605 143611920 154565499 220943249 242922824 213454161 234272651 229962555 213317331 209488838 295957342 211725998 216032281 214691829 431135331 257880768 241686786 216762053 218086136 328985166 220837815 218284596 216312313 214319683 214271325 219030575 222436217 239825320 296573991 235773880 203981045 189446590 185708731 382579729 175940878 172193990 176387589 334884879 208722519 165754706 169503769 200965237 139103476 135561652 289568831 130429746 133279443 156769388 361150135 154462443 183342040 137279919 123747920 114084613 108776361 107283116 105123865 103631484 102435023 100278069 98425803 97120894 94559049 92647136 90617643 88889308 87225160 85852040 84337893 82438175 81405526 78999147 77516179 76386779 74231849 72885367 70746351 69858811 67953055 66765868 65372509 63653388 62411728 61000372 59500529 58341696 57521812 56354581 54386520 53341443 52927384 50630413 49357539 47848548 47018272 46503519 44643259 43497911 42410663 41279647 40192482 39502463 38562766 37773698 35222759 34458680 33876230 32479673 31209766 30365850 29592875 29035457 28367812 27229674 26372275 25898054 25555505 24968412 23753959 23269936 23227518 22695066 21710471 21176955 20601857 20236569 20004844 19319804 18393986 18096955 17296082 17188733 16840513 15670166 15271049 14826521 15357804 14002179 13827443 13126386 12922421 12291672 12597874 11657190 11459238 11581520 10766826 10354715 10252391 10443916 9737638 9953012 8885546 8715375 9021612 9035091 7927433 7759211 7536034 7281256 7644331 6931387 6794666 6974275 6741241 6546644 6224667 5498319 6091985 5104544 4988526 5075334 4333385 4017618 4357278 3985067 3628212 3469888 3366441 3866122 3382820 3063351 3348379 3021319 2391575 2263357 2283341 2263544 2076849 2008142 2374224 1788830 1966099 1688494 1614656 1632424 1543255 1511824 1435361 1360517 1358924 1746468 1690795 1080391 1033566 1456255 905742 880725 932729 1268859 801632 760334 698575 696917 1063164 655091 675535 601858 527519 479684 462317 396671 374043 382168 334811 319494 306304 294786 285515 280022 278821 274855 303220 315830 778544 254790 226584 226892 259248 241107 165469 151197 172888 150515 122063 115610 127487 128926 99212 94380 90918 89276 87128 83774 84592 89458 88584 91447 127156 119073 91345 63001 48500 42958 38095 62191 32412 48868 27593 23637 22308 21392 20799 18845 17980 36035 15808 14964 13455 12667 12075 11213 10559 10228 9604 9374 8718 8067 7793 7378 6964 6600 6393 5991 5810 5405 5156 5016 4798 4604 4333 4259 3978 3923 3677 3583 3259 3084 2958 2874 2706 2522 2470 2471 2270 2227 2050 1874 1964 1856 1784 1722 1575 1540 1445 1461 1358 1225 1211 1164 1072 1088 1013 929 977 924 807 773 819 763 721 681 644 588 597 538 503 481 485 434 419 405 394 376 388 336 364 323 309 313 287 275 225 241 245 212 200 213 168 162 177 149 154 162 175 175 207 115 111 102 88 74 82 85 82 94 73 71 59 56 58 39 36 34 44 47 41 30 36 34 37 34 33 31 31 28 23 25 21 20 27 17 17 14 16 16 14 18 9 8 12 8 11 8 10 11 6 8 5 6 2 4 7 10 5 3 1 3 7 3 1 3 3 6 4 4 1 5 3 4 2 0 1 2 4 0 2 2 1 0 1 2 0 1 1 1 0 1 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
    // max < 0
    "-24.4819 -12.6175 1024 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 3 0 0 0 1 1 0 1 0 1 0 0 0 0 3 2 2 2 0 0 2 2 4 0 1 2 2 1 1 0 1 3 1 2 2 3 2 2 2 1 9 9 5 9 17 10 9 8 4 4 4 5 9 7 9 3 12 7 13 10 12 9 4 9 10 14 13 10 12 18 16 15 20 22 18 12 17 23 22 20 18 20 31 20 30 33 31 28 36 29 33 37 28 38 48 51 48 39 46 35 68 55 64 56 79 66 87 82 83 59 82 74 86 70 92 93 97 99 94 92 100 109 130 128 134 153 152 152 163 182 172 186 173 195 182 217 224 208 212 264 254 246 285 290 266 304 315 344 345 409 395 437 437 396 437 493 543 507 551 550 599 581 688 650 689 699 771 747 751 913 891 880 947 942 1068 1060 1110 1096 1167 1208 1251 1312 1316 1370 1458 1501 1522 1588 1799 1728 1839 1864 1920 1969 2140 2208 2277 2472 2618 2594 2647 2695 2906 2968 3213 3236 3345 3472 3593 3833 3827 3985 4139 4446 4565 4782 4990 5311 5375 5654 5734 5942 6318 6462 6698 7072 8541 35660 10040 9865 10676 10353 10335 10696 11168 11734 11929 12437 12902 13332 14075 14308 15099 15868 16618 18694 58761 19945 22434 20671 20621 21792 22358 23578 23604 23934 24927 25666 27543 27018 28804 29380 31421 36359 55743 46541 40062 39360 40569 41932 41835 43952 72601 46669 47467 49251 49964 51811 52562 54314 56716 57971 60032 61913 64570 65761 68703 70787 73202 113303 91403 84575 88611 90390 134000 99299 99505 101272 104403 123506 129581 120189 120348 124118 129191 133399 137058 144731 148338 190935 208894 168230 177385 181398 187614 200232 637370 244761 253000 239661 243444 251450 281095 258096 282346 273498 284072 290493 299562 373466 321624 329935 339275 354175 361193 399737 387712 399316 414993 432027 449814 504634 477803 496667 517560 529784 548026 572150 595161 621153 668268 1237622 749055 791405 757456 776040 799111 853492 883829 883712 936781 945772 998249 1021699 1061104 1393549 1226423 1316189 1423312 1470827 1534637 1589081 1597358 1710996 1848210 2027547 2217233 2350514 2328073 2438732 2474078 2562581 2871633 2922957 3055742 3108723 3262467 4773865 3587091 3735731 4463169 4406105 4679926 4437677 4894005 4786549 5047926 5693089 5655876 5689014 6419603 6151189 6648580 6628528 7337991 7674408 8011681 7932698 7988401 8470319 8646275 9389563 9935716 9660529 9778487 10240827 10293903 11404105 11040799 11469412 11723622 12111508 12526719 12687955 13896509 14154808 13838654 14155982 15109963 14970065 15790522 15886441 16545165 17042598 17931894 18647781 20142964 19898193 20420633 20953720 22252049 22240446 23509713 24513666 24771753 25561492 26461802 27707581 28685197 29378145 29857300 31193241 32246011 33244081 33602678 35140279 35872415 37271884 38311598 39491447 40498747 41698552 43214154 44398181 45924085 46928842 48469275 49572355 52338257 52983303 54521834 55861209 57879978 60114437 61286530 62571720 65115340 67390927 68879548 71046167 72718276 74629636 77557546 80757826 84136551 87339336 92356649 95308835 100486370 104126661 107849598 111205762 115189340 119903792 124273189 128738583 136744605 143611920 154565499 220943249 242922824 213454161 234272651 229962555 213317331 209488838 295957342 211725998 216032281 214691829 431135331 257880768 241686786 216762053 218086136 328985166 220837815 218284596 216312313 214319683 214271325 219030575 222436217 239825320 296573991 235773880 203981045 189446590 185708731 382579729 175940878 172193990 176387589 334884879 208722519 165754706 169503769 200965237 139103476 135561652 289568831 130429746 133279443 156769388 361150135 154462443 183342040 137279919 123747920 114084613 108776361 107283116 105123865 103631484 102435023 100278069 98425803 97120894 94559049 92647136 90617643 88889308 87225160 85852040 84337893 82438175 81405526 78999147 77516179 76386779 74231849 72885367 70746351 69858811 67953055 66765868 65372509 63653388 62411728 61000372 59500529 58341696 57521812 56354581 54386520 53341443 52927384 50630413 49357539 47848548 47018272 46503519 44643259 43497911 42410663 41279647 40192482 39502463 38562766 37773698 35222759 34458680 33876230 32479673 31209766 30365850 29592875 29035457 28367812 27229674 26372275 25898054 25555505 24968412 23753959 23269936 23227518 22695066 21710471 21176955 20601857 20236569 20004844 19319804 18393986 18096955 17296082 17188733 16840513 15670166 15271049 14826521 15357804 14002179 13827443 13126386 12922421 12291672 12597874 11657190 11459238 11581520 10766826 10354715 10252391 10443916 9737638 9953012 8885546 8715375 9021612 9035091 7927433 7759211 7536034 7281256 7644331 6931387 6794666 6974275 6741241 6546644 6224667 5498319 6091985 5104544 4988526 5075334 4333385 4017618 4357278 3985067 3628212 3469888 3366441 3866122 3382820 3063351 3348379 3021319 2391575 2263357 2283341 2263544 2076849 2008142 2374224 1788830 1966099 1688494 1614656 1632424 1543255 1511824 1435361 1360517 1358924 1746468 1690795 1080391 1033566 1456255 905742 880725 932729 1268859 801632 760334 698575 696917 1063164 655091 675535 601858 527519 479684 462317 396671 374043 382168 334811 319494 306304 294786 285515 280022 278821 274855 303220 315830 778544 254790 226584 226892 259248 241107 165469 151197 172888 150515 122063 115610 127487 128926 99212 94380 90918 89276 87128 83774 84592 89458 88584 91447 127156 119073 91345 63001 48500 42958 38095 62191 32412 48868 27593 23637 22308 21392 20799 18845 17980 36035 15808 14964 13455 12667 12075 11213 10559 10228 9604 9374 8718 8067 7793 7378 6964 6600 6393 5991 5810 5405 5156 5016 4798 4604 4333 4259 3978 3923 3677 3583 3259 3084 2958 2874 2706 2522 2470 2471 2270 2227 2050 1874 1964 1856 1784 1722 1575 1540 1445 1461 1358 1225 1211 1164 1072 1088 1013 929 977 924 807 773 819 763 721 681 644 588 597 538 503 481 485 434 419 405 394 376 388 336 364 323 309 313 287 275 225 241 245 212 200 213 168 162 177 149 154 162 175 175 207 115 111 102 88 74 82 85 82 94 73 71 59 56 58 39 36 34 44 47 41 30 36 34 37 34 33 31 31 28 23 25 21 20 27 17 17 14 16 16 14 18 9 8 12 8 11 8 10 11 6 8 5 6 2 4 7 10 5 3 1 3 7 3 1 3 3 6 4 4 1 5 3 4 2 0 1 2 4 0 2 2 1 0 1 2 0 1 1 1 0 1 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
};

namespace {
class ChooseQuantizationTest : public testing::TestWithParam<tuple<bool, int>> {
};
}; // namespace

INSTANTIATE_TEST_SUITE_P(
    InstantiationName,
    ChooseQuantizationTest,
    testing::Combine(testing::Bool(), testing::Range(0, 3, 1)));

TEST_P(ChooseQuantizationTest, L2MinimizationTest) {
  bool preserve_sparsity;
  int histogram_id;
  tie(preserve_sparsity, histogram_id) = GetParam();
  int precision = 8;

  float min, max;
  int nbins;
  istringstream ist(default_input[histogram_id]);
  ist >> min >> max >> nbins;

  vector<uint64_t> bins;
  for (int i = 0; i < nbins; ++i) {
    uint64_t cnt;
    ist >> cnt;
    bins.push_back(cnt);
  }
  assert(bins.size() == nbins);

  Histogram hist = Histogram(min, max, bins);

  chrono::time_point<chrono::system_clock> begin, end;
  begin = chrono::system_clock::now();
  TensorQuantizationParams qparam =
      L2ErrorMinimization().ChooseQuantizationParams(
          hist, preserve_sparsity, precision);
  end = chrono::system_clock::now();
  double dt = chrono::duration<double>(end - begin).count();

  LOG(INFO) << "L2 error minimizing quantization takes " << dt << " sec.";
  if (preserve_sparsity) {
    if (histogram_id == 0) {
      EXPECT_FLOAT_EQ(qparam.scale, 0.056006733);
      EXPECT_EQ(qparam.zero_point, 128);
      EXPECT_FLOAT_EQ(qparam.Min(), -7.1688619);
      EXPECT_FLOAT_EQ(qparam.Max(), 7.112855);
    } else if (histogram_id == 1) {
      EXPECT_FLOAT_EQ(qparam.scale, 0.089069888);
      EXPECT_EQ(qparam.zero_point, 128);
      EXPECT_FLOAT_EQ(qparam.Min(), -11.400946);
      EXPECT_FLOAT_EQ(qparam.Max(), 11.311875);
    } else {
      EXPECT_FLOAT_EQ(qparam.scale, 0.096339941);
      EXPECT_EQ(qparam.zero_point, 128);
      EXPECT_FLOAT_EQ(qparam.Min(), -12.331512);
      EXPECT_FLOAT_EQ(qparam.Max(), 12.235172);
    }
  } else {
    if (histogram_id == 0) {
      EXPECT_FLOAT_EQ(qparam.scale, 0.053032104);
      EXPECT_EQ(qparam.zero_point, 136);
      EXPECT_FLOAT_EQ(qparam.Min(), -7.2123661);
      EXPECT_FLOAT_EQ(qparam.Max(), 6.3108206);
    } else if (histogram_id == 1) {
      EXPECT_FLOAT_EQ(qparam.scale, 0.08128082);
      EXPECT_EQ(qparam.zero_point, 0);
      EXPECT_FLOAT_EQ(qparam.Min(), 0);
      EXPECT_FLOAT_EQ(qparam.Max(), 20.726608);
    } else {
      EXPECT_FLOAT_EQ(qparam.scale, 0.083512396);
      EXPECT_EQ(qparam.zero_point, 255);
      EXPECT_FLOAT_EQ(qparam.Min(), -21.29566);
      EXPECT_FLOAT_EQ(qparam.Max(), 0);
    }
  }

  LOG(INFO) << qparam.scale << " " << qparam.zero_point << " " << qparam.Min()
            << " " << qparam.Max() << " " << dt;
}
