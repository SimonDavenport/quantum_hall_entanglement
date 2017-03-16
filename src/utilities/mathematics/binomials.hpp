////////////////////////////////////////////////////////////////////////////////
//!
//!                         \author Simon C. Davenport 
//!
//!  \file
//!		Contains a table of binomial numbers and a look up function. The table
//!     excludes cases where the results are either 1, N or that can be related 
//!     by N C K = N K (N-K)
//!
//!                    Copyright (C) Simon C Davenport
//!                                                                             
//!     This program is free software: you can redistribute it and/or modify
//!     it under the terms of the GNU General Public License as published by
//!     the Free Software Foundation, either version 3 of the License,
//!     or (at your option) any later version.
//!                                                                             
//!     This program is distributed in the hope that it will be useful, but
//!     WITHOUT ANY WARRANTY; without even the implied warranty of
//!     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//!     General Public License for more details.
//!                                                                             
//!     You should have received a copy of the GNU General Public License
//!     along with this program. If not, see <http://www.gnu.org/licenses/>.
//!                                                                             
////////////////////////////////////////////////////////////////////////////////

#ifndef _BINOMIALS_HPP_INCLUDED_
#define _BINOMIALS_HPP_INCLUDED_

///////     LIBRARY INCLUSIONS     /////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#if _DEBUG_
#include "../general/debug.hpp"
#endif

namespace utilities
{
    static const int maxBinomial = 64;      //!<    Maximum argument n or r for 
                                            //!<    Tabulated coefficients n choose r
    long int BinomialFromTable(const int n, const int k);    
                                            //!<    Binomial look-up function protorype
    //////////////////////////////////////////////////////////////////////////////////
    //! \brief	This function returns the combinatoric factor input1 Choose input2.
    //!	Inputs are double variables to avoid overflows.
    //!	
    //!	\return	 Value of binomial coefficient (output type T)
    //////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    T Binomial(
	    T input1, 	//!<	First index of binomial
	    T input2)	//!<	Second index of binomial
    {
	    if(input2>input1||input2<0){return 0;}
	    if(input2==0)
	    {
		    return 1;
	    }
	    T cmp = 1;
	    T output = 0;
	    if(input1==input2){return 1;}
	    if(input1>input2){output=input1;
		    while (input1-cmp>input2){output*=(input1-cmp);++cmp;}}
	    else if(input2>input1){output=input2;
		    while (input2-cmp>input1){output*=(input2-cmp);++cmp;}
		    output=1 / output;}
	    T in=input1-input2;
	    cmp=0;
	    while (in-cmp>1){output/=(in-cmp);++cmp;}
	    return (T)round(output);
    }                                        
                                            
    ////////        BINOMIAL TABLE      ////////////////////////////////////////////
    //!
    //! Stores non-trivial binomial coefficients up to 64 choose 64
    //!
    //! Array structure:
    //!
    //! 4c2,
    //! 5c2,
    //! 6c2,6c3,
    //! 7c2,7c3,
    //! 8c2,8c3,8c4,
    //! 9c2,9c3,9c4,
    //! 10c2,10c3,10c4,10c5,
    //! etc...
    //!
    static const long int binomialLookUpTable[] =
    {
    6, 
    10, 15, 20, 21, 
    35, 28, 56, 70, 
    36, 84, 126, 45, 
    120, 210, 252, 55, 
    165, 330, 462, 66, 
    220, 495, 792, 924, 
    78, 286, 715, 1287, 
    1716, 91, 364, 1001, 
    2002, 3003, 3432, 105, 
    455, 1365, 3003, 5005, 
    6435, 120, 560, 1820, 
    4368, 8008, 11440, 12870, 
    136, 680, 2380, 6188, 
    12376, 19448, 24310, 153, 
    816, 3060, 8568, 18564, 
    31824, 43758, 48620, 171, 
    969, 3876, 11628, 27132, 
    50388, 75582, 92378, 190, 
    1140, 4845, 15504, 38760, 
    77520, 125970, 167960, 184756, 
    210, 1330, 5985, 20349, 
    54264, 116280, 203490, 293930, 
    352716, 231, 1540, 7315, 
    26334, 74613, 170544, 319770, 
    497420, 646646, 705432, 253, 
    1771, 8855, 33649, 100947, 
    245157, 490314, 817190, 1144066, 
    1352078, 276, 2024, 10626, 
    42504, 134596, 346104, 735471, 
    1307504, 1961256, 2496144, 2704156, 
    300, 2300, 12650, 53130, 
    177100, 480700, 1081575, 2042975, 
    3268760, 4457400, 5200300, 325, 
    2600, 14950, 65780, 230230, 
    657800, 1562275, 3124550, 5311735, 
    7726160, 9657700, 10400600, 351, 
    2925, 17550, 80730, 296010, 
    888030, 2220075, 4686825, 8436285, 
    13037895, 17383860, 20058300, 378, 
    3276, 20475, 98280, 376740, 
    1184040, 3108105, 6906900, 13123110, 
    21474180, 30421755, 37442160, 40116600, 
    406, 3654, 23751, 118755, 
    475020, 1560780, 4292145, 10015005, 
    20030010, 34597290, 51895935, 67863915, 
    77558760, 435, 4060, 27405, 
    142506, 593775, 2035800, 5852925, 
    14307150, 30045015, 54627300, 86493225, 
    119759850, 145422675, 155117520, 465, 
    4495, 31465, 169911, 736281, 
    2629575, 7888725, 20160075, 44352165, 
    84672315, 141120525, 206253075, 265182525, 
    300540195, 496, 4960, 35960, 
    201376, 906192, 3365856, 10518300, 
    28048800, 64512240, 129024480, 225792840, 
    347373600, 471435600, 565722720, 601080390, 
    528, 5456, 40920, 237336, 
    1107568, 4272048, 13884156, 38567100, 
    92561040, 193536720, 354817320, 573166440, 
    818809200, 1037158320, 1166803110, 561, 
    5984, 46376, 278256, 1344904, 
    5379616, 18156204, 52451256, 131128140, 
    286097760, 548354040, 927983760, 1391975640, 
    1855967520, 2203961430, 2333606220, 595, 
    6545, 52360, 324632, 1623160, 
    6724520, 23535820, 70607460, 183579396, 
    417225900, 834451800, 1476337800, 2319959400, 
    3247943160, 4059928950, 4537567650, 630, 
    7140, 58905, 376992, 1947792, 
    8347680, 30260340, 94143280, 254186856, 
    600805296, 1251677700, 2310789600, 3796297200, 
    5567902560, 7307872110, 8597496600, 9075135300, 
    666, 7770, 66045, 435897, 
    2324784, 10295472, 38608020, 124403620, 
    348330136, 854992152, 1852482996, 3562467300, 
    6107086800, 9364199760, 12875774670, 15905368710, 
    17672631900, 703, 8436, 73815, 
    501942, 2760681, 12620256, 48903492, 
    163011640, 472733756, 1203322288, 2707475148, 
    5414950296, 9669554100, 15471286560, 22239974430, 
    28781143380, 33578000610, 35345263800, 741, 
    9139, 82251, 575757, 3262623, 
    15380937, 61523748, 211915132, 635745396, 
    1676056044, 3910797436, 8122425444, 15084504396, 
    25140840660, 37711260990, 51021117810, 62359143990, 
    68923264410, 780, 9880, 91390, 
    658008, 3838380, 18643560, 76904685, 
    273438880, 847660528, 2311801440, 5586853480, 
    12033222880, 23206929840, 40225345056, 62852101650, 
    88732378800, 113380261800, 131282408400, 137846528820, 
    820, 10660, 101270, 749398, 
    4496388, 22481940, 95548245, 350343565, 
    1121099408, 3159461968, 7898654920, 17620076360, 
    35240152720, 63432274896, 103077446706, 151584480450, 
    202112640600, 244662670200, 269128937220, 861, 
    11480, 111930, 850668, 5245786, 
    26978328, 118030185, 445891810, 1471442973, 
    4280561376, 11058116888, 25518731280, 52860229080, 
    98672427616, 166509721602, 254661927156, 353697121050, 
    446775310800, 513791607420, 538257874440, 903, 
    12341, 123410, 962598, 6096454, 
    32224114, 145008513, 563921995, 1917334783, 
    5752004349, 15338678264, 36576848168, 78378960360, 
    151532656696, 265182149218, 421171648758, 608359048206, 
    800472431850, 960566918220, 1052049481860, 946, 
    13244, 135751, 1086008, 7059052, 
    38320568, 177232627, 708930508, 2481256778, 
    7669339132, 21090682613, 51915526432, 114955808528, 
    229911617056, 416714805914, 686353797976, 1029530696964, 
    1408831480056, 1761039350070, 2012616400080, 2104098963720, 
    990, 14190, 148995, 1221759, 
    8145060, 45379620, 215553195, 886163135, 
    3190187286, 10150595910, 28760021745, 73006209045, 
    166871334960, 344867425584, 646626422970, 1103068603890, 
    1715884494940, 2438362177020, 3169870830126, 3773655750150, 
    4116715363800, 1035, 15180, 163185, 
    1370754, 9366819, 53524680, 260932815, 
    1101716330, 4076350421, 13340783196, 38910617655, 
    101766230790, 239877544005, 511738760544, 991493848554, 
    1749695026860, 2818953098830, 4154246671960, 5608233007146, 
    6943526580276, 7890371113950, 8233430727600, 1081, 
    16215, 178365, 1533939, 10737573, 
    62891499, 314457495, 1362649145, 5178066751, 
    17417133617, 52251400851, 140676848445, 341643774795, 
    751616304549, 1503232609098, 2741188875414, 4568648125690, 
    6973199770790, 9762479679106, 12551759587422, 14833897694226, 
    16123801841550, 1128, 17296, 194580, 
    1712304, 12271512, 73629072, 377348994, 
    1677106640, 6540715896, 22595200368, 69668534468, 
    192928249296, 482320623240, 1093260079344, 2254848913647, 
    4244421484512, 7309837001104, 11541847896480, 16735679449896, 
    22314239266528, 27385657281648, 30957699535776, 32247603683100, 
    1176, 18424, 211876, 1906884, 
    13983816, 85900584, 450978066, 2054455634, 
    8217822536, 29135916264, 92263734836, 262596783764, 
    675248872536, 1575580702584, 3348108992991, 6499270398159, 
    11554258485616, 18851684897584, 28277527346376, 39049918716424, 
    49699896548176, 58343356817424, 63205303218876, 1225, 
    19600, 230300, 2118760, 15890700, 
    99884400, 536878650, 2505433700, 10272278170, 
    37353738800, 121399651100, 354860518600, 937845656300, 
    2250829575120, 4923689695575, 9847379391150, 18053528883775, 
    30405943383200, 47129212243960, 67327446062800, 88749815264600, 
    108043253365600, 121548660036300, 126410606437752, 1275, 
    20825, 249900, 2349060, 18009460, 
    115775100, 636763050, 3042312350, 12777711870, 
    47626016970, 158753389900, 476260169700, 1292706174900, 
    3188675231420, 7174519270695, 14771069086725, 27900908274925, 
    48459472266975, 77535155627160, 114456658306760, 156077261327400, 
    196793068630200, 229591913401900, 247959266474052, 1326, 
    22100, 270725, 2598960, 20358520, 
    133784560, 752538150, 3679075400, 15820024220, 
    60403728840, 206379406870, 635013559600, 1768966344600, 
    4481381406320, 10363194502115, 21945588357420, 42671977361650, 
    76360380541900, 125994627894135, 191991813933920, 270533919634160, 
    352870329957600, 426384982032100, 477551179875952, 495918532948104, 
    1378, 23426, 292825, 2869685, 
    22957480, 154143080, 886322710, 4431613550, 
    19499099620, 76223753060, 266783135710, 841392966470, 
    2403979904200, 6250347750920, 14844575908435, 32308782859535, 
    64617565719070, 119032357903550, 202355008436035, 317986441828055, 
    462525733568080, 623404249591760, 779255311989700, 903936161908052, 
    973469712824056, 1431, 24804, 316251, 
    3162510, 25827165, 177100560, 1040465790, 
    5317936260, 23930713170, 95722852680, 343006888770, 
    1108176102180, 3245372870670, 8654327655120, 21094923659355, 
    47153358767970, 96926348578605, 183649923622620, 321387366339585, 
    520341450264090, 780512175396135, 1085929983159840, 1402659561581460, 
    1683191473897752, 1877405874732108, 1946939425648112, 1485, 
    26235, 341055, 3478761, 28989675, 
    202927725, 1217566350, 6358402050, 29248649430, 
    119653565850, 438729741450, 1451182990950, 4353548972850, 
    11899700525790, 29749251314475, 68248282427325, 144079707346575, 
    280576272201225, 505037289962205, 841728816603675, 1300853625660225, 
    1866442158555975, 2488589544741300, 3085851035479212, 3560597348629859, 
    3824345300380220, 1540, 27720, 367290, 
    3819816, 32468436, 231917400, 1420494075, 
    7575968400, 35607051480, 148902215280, 558383307300, 
    1889912732400, 5804731963800, 16253249498640, 41648951840265, 
    97997533741800, 212327989773900, 424655979547800, 785613562163430, 
    1346766106565880, 2142582442263900, 3167295784216200, 4355031703297276, 
    5574440580220512, 6646448384109072, 7384942649010080, 7648690600760440, 
    1596, 29260, 395010, 4187106, 
    36288252, 264385836, 1652411475, 8996462475, 
    43183019880, 184509266760, 707285522580, 2448296039700, 
    7694644696200, 22057981462440, 57902201338905, 139646485582065, 
    310325523515700, 636983969321700, 1210269541711230, 2132379668729309, 
    3489348548829779, 5309878226480098, 7522327487513474, 9929472283517786, 
    12220888964329584, 14031391033119150, 15033633249770518, 1653, 
    30856, 424270, 4582116, 40475358, 
    300674088, 1916797311, 10648873950, 52179482355, 
    227692286640, 891794789340, 3155581562280, 10142940735900, 
    29752626158640, 79960182801345, 197548686920970, 449972009097765, 
    947309492837400, 1847253511032930, 3342649210440539, 5621728217559088, 
    8799226775309878, 12832205713993576, 17451799771031262, 22150361247847372, 
    26252279997448736, 29065024282889668, 30067266499541040, 1711, 
    32509, 455126, 5006386, 45057474, 
    341149446, 2217471399, 12565671261, 62828356305, 
    279871768995, 1119487075980, 4047376351620, 13298522298180, 
    39895566894540, 109712808959985, 277508869722315, 647520696018735, 
    1397281501935165, 2794563003870330, 5189902721473470, 8964377427999630, 
    14420954992868968, 21631432489303456, 30284005485024836, 39602161018878640, 
    48402641245296112, 55317304280338416, 59132290782430712, 1770, 
    34220, 487635, 5461512, 50063860, 
    386206920, 2558620845, 14783142660, 75394027566, 
    342700125300, 1399358844975, 5166863427600, 17345898649800, 
    53194089192720, 149608375854525, 387221678682300, 925029565741050, 
    2044802197953900, 4191844505805495, 7984465725343800, 14154280149473100, 
    23385332420868596, 36052387482172424, 51915437974328280, 69886166503903464, 
    88004802264174736, 103719945525634512, 114449595062769136, 118264581564861408, 
    1830, 35990, 521855, 5949147, 
    55525372, 436270780, 2944827765, 17341763505, 
    90177170226, 418094152866, 1742058970275, 6566222272575, 
    22512762077400, 70539987842520, 202802465047245, 536830054536825, 
    1312251244423350, 2969831763694950, 6236646703759394, 12176310231149296, 
    22138745874816904, 37539612570341696, 59437719903041024, 87967825456500704, 
    121801604478231760, 157890968768078240, 191724747789809280, 218169540588403680, 
    232714176627630560, 1891, 37820, 557845, 
    6471002, 61474519, 491796152, 3381098545, 
    20286591270, 107518933731, 508271323092, 2160153123141, 
    8308281242850, 29078984349975, 93052749919920, 273342452889765, 
    739632519584070, 1849081298960175, 4282083008118300, 9206478467454344, 
    18412956934908692, 34315056105966200, 59678358445158600, 96977332473382736, 
    147405545359541760, 209769429934732448, 279692573246309984, 349615716557887424, 
    409894288378212928, 450883717216034176, 465428353255261120, 1953, 
    39711, 595665, 7028847, 67945521, 
    553270671, 3872894697, 23667689815, 127805525001, 
    615790256823, 2668424446233, 10468434365991, 37387265592825, 
    122131734269895, 366395202809685, 1012974972473835, 2588713818544245, 
    6131164307078474, 13488561475572646, 27619435402363036, 52728013040874880, 
    93993414551124800, 156655690918541344, 244382877832924448, 357174975294274176, 
    489462003181042432, 629308289804197376, 759510004936100352, 860778005594247168, 
    916312070471295488, 2016, 41664, 635376, 
    7624512, 74974368, 621216192, 4426165368, 
    27540584512, 151473214816, 743595781824, 3284214703056, 
    13136858812224, 47855699958816, 159518999862720, 488526937079580, 
    1379370175283520, 3601688791018080, 8719878125622720, 19619725782651120, 
    41107996877935680, 80347448443237920, 146721427591999648, 250649105469666176, 
    401038568751465792, 601557853127198592, 846636978475316608, 1118770292985239808, 
    1388818294740297728, 1620288010530347264, 1777090076065542656, 1832624140942590976 
    };

    ////////  CODE TO GENERATE THE TABLE
    /*
    #include <iostream>
    #include <math.h>
    #include <boost/math/special_functions/binomial.hpp> //  For Binomial coefficients
    int main(int, char**)
    {
        int counter=0;
        for(int i=4; i<=64; ++i)
        {
            for(int j=2; j<=floor((double)i/2); ++j, ++counter)
            {
                //std::cout<<"Binomial<"<<i<<","<<j<<">::val,";
                std::cout<<(uint64_t)round(boost::math::binomial_coefficient<double>(i,j))<<", ";
                if(counter % 4 ==0) std::cout<<std::endl;
            }
        }
    }
    */
}   //  End namespace utilities
#endif
