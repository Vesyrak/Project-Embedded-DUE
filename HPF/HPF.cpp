#include "Arduino.h"
#include "Convolution.h"
#include "HPF.h"
float kernel[]= {-3.9083967872404766e-05, -3.2678177565162072e-05,-6.493211618646389e-06,2.3714893871837965e-05,3.9701019204988055e-05,3.1741697307494257e-05,4.5442127322413422e-06,-2.5533871672840615e-05,-4.0314531763522918e-05,-3.077634317147254e-05,-2.555590417143041e-06,2.7379957579601154e-05,4.0924316557847335e-05,2.9775290848442995e-05,5.1810653846835338e-07,-2.9258980192346208e-05,-4.1529032871431321e-05,-2.8730751499825938e-05,1.5776541104088924e-06,3.1176041579613146e-05,4.212615363081324e-05,2.763402281123596e-05,-3.7411780521827705e-06,-3.3135421659745654e-05,-4.2711938872366331e-05,-2.6475548270073859e-05,5.9819140645991619e-06,3.5140486243286357e-05,4.3281417619577972e-05,2.524498446391039e-05,-8.3091614102569097e-06,-3.7193599362302222e-05,-4.3828378443691099e-05,-2.3931276151123861e-05,1.0731955976730166e-05,3.9296040499209866e-05,4.4345368938411027e-05,2.2522738810224105e-05,-1.3258954966925911e-05,-4.1447927310907659e-05,-4.4823704295580136e-05,-2.1007148330074762e-05,1.5898320797233076e-05,4.3648144424166175e-05,4.5253485123502102e-05,1.9371837460259483e-05,-1.8657604875447823e-05,-4.5894278855327099e-05,-4.5623624603112179e-05,-1.7603798599089426e-05,2.1543631941913268e-05,4.8182562581375203e-05,4.5921885029704704e-05,1.5689792456732008e-05,-2.4562385665406094e-05,-5.0507822760641412e-05,-4.6134923739573368e-05,-1.3616462092549847e-05,2.7718896190273164e-05,5.286344006972482e-05,4.6248348372032483e-05,1.1370451789460097e-05,-3.1017130332764293e-05,-5.5241315588944472e-05,-4.6246781367967525e-05,-8.9385301938381397e-06,3.4459885122732225e-05,5.7631846631743368e-05,4.6113933556666898e-05,6.3077171177450281e-06,-3.8048685381543165e-05,-6.0023911874249379e-05,-4.5832686633288954e-05,-3.4654133708561664e-06,4.1783686018462905e-05,6.2404866099710255e-05,4.5385184280351504e-05,3.9953296291537202e-07,-4.5663579715627797e-05,-6.4760544829009107e-05,-4.4752931638115274e-05,2.9013630063843756e-06,4.968551065624368e-05,6.7075279063049921e-05,4.3916902781118346e-05,-6.4479314739059533e-06,-5.3844994931911043e-05,-6.9331920315731234e-05,-4.2857655811372343e-05,1.0249912277595197e-05,5.8135848242770808e-05,7.1511876067671668e-05,4.1555455133411947e-05,-1.4315993495075376e-05,-6.2550121478900387e-05,-7.3595155721024809e-05,-3.99904004323772e-05,1.8653678003681528e-05,6.7078044742841848e-05,7.5560427084861713e-05,3.8142561834154268e-05,-2.3269152016994225e-05,-7.1707980341714135e-05,-7.7385083368906727e-05,-3.5992120686146112e-05,2.8167156357238209e-05,7.6426385242831183e-05,7.9045320611162022e-05,3.351951535914297e-05,-3.3350861223815493e-05,-8.1217783449575361e-05,-8.0516225412300953e-05,-3.0705591434758378e-05,3.8821745215306794e-05,8.6064748714324529e-05,8.1771872797014485e-05,2.7531755609609077e-05,-4.4579479356008813e-05,-9.0947897962923564e-05,-8.2785433969861485e-05,-2.3980132616547779e-05,5.0621816867959487e-05,9.5845895760403489e-05,8.3529293681005044e-05,2.0033724435554231e-05,-5.6944489415979588e-05,-0.00010073547010085498,-8.397517686554369e-05,-1.5676571041920137e-05,6.3541110535935392e-05,0.00010559143975551558,8.4094284169493178e-05,1.0893911917825688e-05,-7.0403086935861881e-05,-0.00011038675336263077,-8.3857435925784667e-05,-5.6723475348333285e-06,7.751953833529171e-05,0.00011509254039052302,8.3235224095471629e-05,-5.7466966513424757e-19,-8.4877226480735405e-05,-0.00011967817405194163,-8.219817164252234e-05,6.1333279531218561e-06,9.2460493944213147e-05,0.00012411134619328722,8.0716898765850281e-05,-1.2735996455325172e-05,-0.00010025121327778616,-0.00012835815412700998,-7.876229536930054e-05,1.9814375305118448e-05,0.00010822874705973757,0.00013238319931956771,7.63056991098989e-05,-2.7372694915852026e-05,-0.00011636991932810772,-0.00013614969779108602,-7.3319078326401687e-05,3.5412902234267134e-05,0.00012464899885420772,0.00013961960202654153,6.9775219114973807e-05,-4.3934522451167991e-05,-0.00013303769466331802,-0.00014275373414208186,-6.5647915786131976e-05,5.2934527313616402e-05,0.00014150516416166191,0.00014551192999438139,6.0912163907792607e-05,-6.2407210833393184e-05,-0.0001500180341786332,-0.00014785319386582336,-5.5544355112758862e-05,7.2344073167586584e-05,0.00015854043518078703,0.00014973586330424308,4.9522472826279009e-05,-8.273371342503912e-05,-0.00016703404886004732,-0.00015111778364293557,-4.2826288049981003e-05,9.3561732125973162e-05,0.00017545816924270519,0.00015195649167526687,3.5437554322522508e-05,-0.00010481064401259799,-0.00018376977740872303,-0.00015220940790836712,-2.7340200965652874e-05,0.0001164598018749895,0.0001919236298524398,0.00015183403677270611,1.8520523716053447e-05,-0.00012848533202013154,-0.0001998723604566344,-0.00015078817411855671,-8.9673718394782847e-06,0.00014086008197169804,0.00020756659599202926,0.00014903012128730301,-1.3276691767593674e-06,-0.00015355358094521892,-0.00021495508499414634,-0.00014651890500506923,1.2370100252561542e-05,0.00016653201359685584,0.00022198483980907866,0.00014321450230828258,-2.4162337556906404e-05,-0.00017975820749530587,-0.00022860129153961977,-0.00013907806967648068,3.6703548442077042e-05,0.00019319163471435971,0.00023474845756350307,0.00013407217551617578,-4.9989495333631214e-05,-0.00020678842788974746,-0.00024036912123650514,-0.00012816103511205769,6.4012388418578696e-05,0.00022050141102728101,0.00024540502333520841,0.00012131074713729611,-7.8760747950030861e-05,-0.00023428014529117166,-0.00024979706473747087,-0.00011348953079473805,9.4219276957622648e-05,0.000248070989940887,0.00025348551978356218,0.00010466796264411082,-0.00011036874512093067,-0.00026181717852333892,-0.00025641025970745914,-9.4819212158419198e-05,0.00012718588452615976,0.00027545891036390667,0.0002585109854765904,8.3919275044191965e-05,-0.00014464329798650062,-0.00028893345733587447,-0.00025972746932946832,-7.1947203356989689e-05,0.00016270938056221616,0.00030217528582269484,0.00025999980425410918,5.8885331443888573e-05,-0.00018134825486953833,-0.00031511619372217756,-0.00025926866060689758,-4.471949675029469e-05,0.00020051972071601115,0.00032768546227587186,0.00025747554903095867,2.9439254537613362e-05,-0.00022017921954614139,-0.00033981002244136248,-0.00025456308879629879,-1.3038085573268152e-05,0.0002402778141235198,0.00035141463545969873,0.00025047528065009957,-4.4864041268939551e-06,-0.00026076218381590645,-0.00036242208720544609,-0.00024515778323616681,2.3132292399564845e-05,0.00028157463578629301,0.0003727533958429626,0.00023855819211644194,-4.2893159746392137e-05,-0.00030265313232789057,-0.00038232803224969009,-0.00023062632040625087,6.375791869221706e-05,0.00032393133451277177,0.00039106415260592512,0.00022131448001715901,-8.5710654486384878e-05,-0.00034533866225445933,-0.00039887884249094926,-0.00021057776248908875,0.00010873047790150323,0.00036680037081239796,0.00040568837176763244,0.00019837431838482975,-0.00013279139083794607,-0.00038823764369306488,-0.000411408459482276,-0.00018466563421734998,0.00015786216539023654,0.0004095677018271049,0.00041595454795340168,0.00016941680588133048,-0.00018390623697621186,-0.00043070392882600249,-0.00041924208517313201,-0.00015259680756788012,0.00021088161206897493,0.00045155601204410821,0.00042118681459727894,0.00013417875515284161,-0.00023874079100788548,-0.00047203009909371394,-0.0004217050713564497,-0.00011414016306712218,0.00026743070629513087,0.00049202896938229431,0.00042071408387955818,9.2463193679401549e-05,-0.00029689267671199231,-0.00051145222016142644,-0.00041813227988439516,-6.9134898250785675e-05,0.00032706237751102025,0.00053019646649758148,0.00041387959565617063,4.4147448554216722e-05,-0.00035786982685983329,-0.00054815555449513127,-0.00040787778750602291,-1.7498358291909444e-05,0.00038923938862606947,0.00056522078702242852,0.00040005074427624328,-1.0809306511451116e-05,-0.00042108979150387078,-0.00058128116111209427,-0.00039032479973772846,4.076672890970808e-05,0.00045333416438872047,0.00059622361612740463,0.00037862904370920261,-7.2359154943202829e-05,-0.00048588008780987775,-0.00060993329170753205,-0.00036489563071504617,0.00010556572070339705,0.00051862966112739323,0.00062229379442555236,0.00034906008499187145,-0.00014035929313305253,-0.00055147958509512926,-0.00063318747201442647,-0.00033106160065040328,0.00017670632506560437,0.00058432125927982944,0.00064249569393769548,0.00031084333580201325,-0.00021456672492328779,-0.0006170408937114987,-0.00065009913700284333,-0.00028835269946502569,0.0002538937414047922,0.00064951963401915693,0.00065587807463654926,0.00026354163007832274,-0.00029463386339514041,-0.00068163369918053157,-0.00065971266836117686,-0.00023636686446494495,0.00033672673522645537,0.00071325453088148479,0.00066148325993153803,0.00020679019611040639,-0.00038010508730563131,-0.00074424895334249759,-0.0006610706625082408,-0.00017477872164490103,0.00042469468200303947,0.00077447934232238193,0.00065835644915983435,0.00014030507445003277,-0.00047041427456699967,-0.00080380380185442982,-0.0006532232368976112,-0.00010334764434420404,0.00051717558868707026,0.000832076347104381,0.00064555496435560818,6.3890782341338292e-05,-0.00056488330617888776,-0.00085914709156287078,-0.00063523716113019044,-2.192498951978347e-05,0.00061343507009832098,0.0008848624365941309,0.00062215720668998612,-2.2552910912820962e-05,-0.00066272150041641351,-0.00090906526115645629,-0.00060620457665282656,6.9539619221975954e-05,0.00071262622119245254,0.00093159510928464222,0.00058727107410306526,-0.00011902522322382006,-0.00076302589797305309,-0.00095228837267744297,-0.00056525104348367306,0.00017099308158533691,0.0008137902839131276,0.00097097846545972854,0.00054004156444392368,-0.00022541972703371216,-0.00086478227286142836,-0.00098749598788448636,-0.00051154262284686092,0.00028227479009376239,0.00091585795737066978,0.0010016688753985137,0.00047965725594149682,-0.00034152094390522221,-0.00096686668927975234,-0.0010133225291097401,-0.00044429166847202511,0.00040311387059835223,0.0010176511401634545,0.001022279923255965,0.00040535531622902841,-0.00046700224963406819,-0.0010680473585502285,-0.001028361684772428,-0.00036276095323296717,0.00053312776843675237,0.0011178848203592536,0.0010313861394781521,0.00031642463837120685,-0.00060142515557160578,-0.0011669864684969499,-0.0010311693187305534,-0.0002662656968752409,0.00067182223663680019,0.001215168736964857,0.0010275249196181457,0.00021220663150630503,-0.00074424001296150444,-0.0012622415541528082,-0.0010202642108458546,-0.0001541729777041476,0.00081859276311694554,0.0013080083192019041,0.0010091958753915609,9.2093096216131864e-05,-0.00089478816716679038,-0.0013522658444000218,-0.00099412577973671356,-2.5897895843898611e-05,0.00097272745349820237,0.0013948042554873408,0.00097485665795894597,-4.4479522118907698e-05,-0.0010523055679936312,-0.0014354068404663681,-0.00095118769716253358,0.00011910430746352192,0.0011334113652187255,0.0014738498359838936,0.0009229140085478838,-0.00019804040391794631,-0.0012159278212213473,-0.0015099021385258022,-0.00088982596580010635,0.00028135120441846571,0.0012997322674535715,0.0015433249254683263,0.00085170838929858378,-0.00036910033424924295,-0.001384696645250283,-0.001573871168371505,-0.00080833955078577944,0.00046135258031305748,0.0014706877802178118,0.0016012850176689382,0.00075948996840510298,-0.00055817498826127678,-0.0015575676758111149,-0.0016253010339557954,-0.00070492095621375753,0.00065963815348100518,0.0016451938253021514,0.0016456432362192371,0.00064438288510630887,-0.00076581773723569146,-0.0017334195412714156,-0.0016620239313485789,-0.00057761310319244541,0.00087679624584661889,0.001822094301684754,0.0016741422817949502,0.00050433345257625169,-0.00099266511905586781,-0.0019110641115519162,-0.0016816825589101826,-0.00042424730556805609,0.0011135271840885966,0.0020001718791005244,0.0016843120177428999,0.00033703602580154041,-0.0012394995450614437,-0.0020892578053400808,-0.0016816783141897697,-0.00024235473744084007,0.0013707169940888513,0.0021781597858354148,0.0016734063664348689,0.00013982725718793913,-0.00150733605183071,-0.0022667138234577981,-0.0016590945382718646,-2.9040007174448355e-05,0.001649539772802496,0.0023547544508351146,0.0016383099904430005,-9.0465320630472078e-05,-0.0017975434865781827,-0.0024421151611800757,-0.0016105830051498129,0.00021920063981268229,0.0019516016928707892,0.0025286288461377837,0.0015754000350804427,-0.00035774225755784276,-0.0021120163902851839,-0.0026141282392610748,-0.0015321951570316313,0.00050674405644081562,0.0022791472007905656,0.0026984463636941652,0.0014803395149521037,-0.0006669536960820147,-0.0024534237624432346,-0.0027814169826223811,-0.001419128208681631,0.00083923265703698393,0.0026353610127836514,0.0028628750510281448,0.0013477639093494574,-0.0010245812176496402,-0.0028255781908860774,-0.0029426571672811425,-0.0012653362406374162,0.00122416982577388,0.0030248226711937021,0.0030206020230836962,0.0011707956276963793,-0.0014393788469467966,-0.0032340001428010907,-0.0030965508502908568,-0.0010629198384484774,0.0016718494078519571,0.0034542132180417329,0.0031703478631286757,0.00094027075800938041,-0.0019235491148784387,-0.0036868113778857755,-0.0032418406943435069,-0.0008011379412481629,0.0021968579782671335,0.0039334563704131126,0.0033108808238298732,0.00064346401480851125,-0.0024946821774529623,-0.0041962089835182815,-0.0033773239983048795,-0.00046474477896279065,0.0028206067938637541,0.0044776458596072323,0.0034410306406221711,0.00026189344533378078,-0.003179104032129113,-0.0047810192878744639,-0.0035018662473495807,-3.1053081087584004e-05,0.0035758219777985308,0.0051104796963237879,0.0035597017732701798,-0.00023266730909856986,-0.0040179927595787469,-0.005471391638555134,-0.00361441400150736,0.00053557192615711962,0.0045150220173414777,0.0058707926644110953,0.0036658858980202617,-0.00088593579193177409,-0.0050793611943866683,-0.0063180767186213158,-0.0037140069492662127,0.0012948471453248594,0.0057278347945347325,0.0068260417706827933,0.0037586734818817608,-0.0017775200411535045,-0.0064837258999939891,-0.0074125504170531138,-0.0037997889632931147,0.0023554147144238865,0.0073801786538501765,0.0081032673254554256,0.003837264282229916,-0.0030598119013992243,-0.0084660022508943403,-0.0089363872057022734,-0.0038710180081839214,0.0039381543450921685,0.0098161178282966388,0.0099712751966027444,0.0039009766289241528,-0.0050660251308610651,-0.011551648284760125,-0.01130540157909427,-0.0039270747652549749,0.0065716250485776439,0.013881923827486431,0.013110629924429556,0.0039492553622802922,-0.0086911685618633484,-0.017202494358483717,-0.015720734935066948,-0.0039674698565170243,0.01191291307080434,0.022361162355432999,0.01988049087369971,0.0039816783182839597,-0.017435433425556399,-0.031562493603431559,-0.02765899466467937,-0.0039918495688758965,0.029197122599126147,0.052890369041867967,0.047746937900155675,0.0039979612721200821,-0.072141695789971733,-0.15910115324199717,-0.22788839746030662,0.746,-0.22788839746030662,-0.15910115324199717,-0.072141695789971733,0.0039979612721200821,0.047746937900155675,0.052890369041867967,0.029197122599126147,-0.0039918495688758965,-0.02765899466467937,-0.031562493603431559,-0.017435433425556399,0.0039816783182839597,0.01988049087369971,0.022361162355432999,0.01191291307080434,-0.0039674698565170243,-0.015720734935066948,-0.017202494358483717,-0.0086911685618633484,0.0039492553622802922,0.013110629924429556,0.013881923827486431,0.0065716250485776439,-0.0039270747652549749,-0.01130540157909427,-0.011551648284760125,-0.0050660251308610651,0.0039009766289241528,0.0099712751966027444,0.0098161178282966388,0.0039381543450921685,-0.0038710180081839214,-0.0089363872057022734,-0.0084660022508943403,-0.0030598119013992243,0.003837264282229916,0.0081032673254554256,0.0073801786538501765,0.0023554147144238865,-0.0037997889632931147,-0.0074125504170531138,-0.0064837258999939891,-0.0017775200411535045,0.0037586734818817608,0.0068260417706827933,0.0057278347945347325,0.0012948471453248594,-0.0037140069492662127,-0.0063180767186213158,-0.0050793611943866683,-0.00088593579193177409,0.0036658858980202617,0.0058707926644110953,0.0045150220173414777,0.00053557192615711962,-0.00361441400150736,-0.005471391638555134,-0.0040179927595787469,-0.00023266730909856986,0.0035597017732701798,0.0051104796963237879,0.0035758219777985308,-3.1053081087584004e-05,-0.0035018662473495807,-0.0047810192878744639,-0.003179104032129113,0.00026189344533378078,0.0034410306406221711,0.0044776458596072323,0.0028206067938637541,-0.00046474477896279065,-0.0033773239983048795,-0.0041962089835182815,-0.0024946821774529623,0.00064346401480851125,0.0033108808238298732,0.0039334563704131126,0.0021968579782671335,-0.0008011379412481629,-0.0032418406943435069,-0.0036868113778857755,-0.0019235491148784387,0.00094027075800938041,0.0031703478631286757,0.0034542132180417329,0.0016718494078519571,-0.0010629198384484774,-0.0030965508502908568,-0.0032340001428010907,-0.0014393788469467966,0.0011707956276963793,0.0030206020230836962,0.0030248226711937021,0.00122416982577388,-0.0012653362406374162,-0.0029426571672811425,-0.0028255781908860774,-0.0010245812176496402,0.0013477639093494574,0.0028628750510281448,0.0026353610127836514,0.00083923265703698393,-0.001419128208681631,-0.0027814169826223811,-0.0024534237624432346,-0.0006669536960820147,0.0014803395149521037,0.0026984463636941652,0.0022791472007905656,0.00050674405644081562,-0.0015321951570316313,-0.0026141282392610748,-0.0021120163902851839,-0.00035774225755784276,0.0015754000350804427,0.0025286288461377837,0.0019516016928707892,0.00021920063981268229,-0.0016105830051498129,-0.0024421151611800757,-0.0017975434865781827,-9.0465320630472078e-05,0.0016383099904430005,0.0023547544508351146,0.001649539772802496,-2.9040007174448355e-05,-0.0016590945382718646,-0.0022667138234577981,-0.00150733605183071,0.00013982725718793913,0.0016734063664348689,0.0021781597858354148,0.0013707169940888513,-0.00024235473744084007,-0.0016816783141897697,-0.0020892578053400808,-0.0012394995450614437,0.00033703602580154041,0.0016843120177428999,0.0020001718791005244,0.0011135271840885966,-0.00042424730556805609,-0.0016816825589101826,-0.0019110641115519162,-0.00099266511905586781,0.00050433345257625169,0.0016741422817949502,0.001822094301684754,0.00087679624584661889,-0.00057761310319244541,-0.0016620239313485789,-0.0017334195412714156,-0.00076581773723569146,0.00064438288510630887,0.0016456432362192371,0.0016451938253021514,0.00065963815348100518,-0.00070492095621375753,-0.0016253010339557954,-0.0015575676758111149,-0.00055817498826127678,0.00075948996840510298,0.0016012850176689382,0.0014706877802178118,0.00046135258031305748,-0.00080833955078577944,-0.001573871168371505,-0.001384696645250283,-0.00036910033424924295,0.00085170838929858378,0.0015433249254683263,0.0012997322674535715,0.00028135120441846571,-0.00088982596580010635,-0.0015099021385258022,-0.0012159278212213473,-0.00019804040391794631,0.0009229140085478838,0.0014738498359838936,0.0011334113652187255,0.00011910430746352192,-0.00095118769716253358,-0.0014354068404663681,-0.0010523055679936312,-4.4479522118907698e-05,0.00097485665795894597,0.0013948042554873408,0.00097272745349820237,-2.5897895843898611e-05,-0.00099412577973671356,-0.0013522658444000218,-0.00089478816716679038,9.2093096216131864e-05,0.0010091958753915609,0.0013080083192019041,0.00081859276311694554,-0.0001541729777041476,-0.0010202642108458546,-0.0012622415541528082,-0.00074424001296150444,0.00021220663150630503,0.0010275249196181457,0.001215168736964857,0.00067182223663680019,-0.0002662656968752409,-0.0010311693187305534,-0.0011669864684969499,-0.00060142515557160578,0.00031642463837120685,0.0010313861394781521,0.0011178848203592536,0.00053312776843675237,-0.00036276095323296717,-0.001028361684772428,-0.0010680473585502285,-0.00046700224963406819,0.00040535531622902841,0.001022279923255965,0.0010176511401634545,0.00040311387059835223,-0.00044429166847202511,-0.0010133225291097401,-0.00096686668927975234,-0.00034152094390522221,0.00047965725594149682,0.0010016688753985137,0.00091585795737066978,0.00028227479009376239,-0.00051154262284686092,-0.00098749598788448636,-0.00086478227286142836,-0.00022541972703371216,0.00054004156444392368,0.00097097846545972854,0.0008137902839131276,0.00017099308158533691,-0.00056525104348367306,-0.00095228837267744297,-0.00076302589797305309,-0.00011902522322382006,0.00058727107410306526,0.00093159510928464222,0.00071262622119245254,6.9539619221975954e-05,-0.00060620457665282656,-0.00090906526115645629,-0.00066272150041641351,-2.2552910912820962e-05,0.00062215720668998612,0.0008848624365941309,0.00061343507009832098,-2.192498951978347e-05,-0.00063523716113019044,-0.00085914709156287078,-0.00056488330617888776,6.3890782341338292e-05,0.00064555496435560818,0.000832076347104381,0.00051717558868707026,-0.00010334764434420404,-0.0006532232368976112,-0.00080380380185442982,-0.00047041427456699967,0.00014030507445003277,0.00065835644915983435,0.00077447934232238193,0.00042469468200303947,-0.00017477872164490103,-0.0006610706625082408,-0.00074424895334249759,-0.00038010508730563131,0.00020679019611040639,0.00066148325993153803,0.00071325453088148479,0.00033672673522645537,-0.00023636686446494495,-0.00065971266836117686,-0.00068163369918053157,-0.00029463386339514041,0.00026354163007832274,0.00065587807463654926,0.00064951963401915693,0.0002538937414047922,-0.00028835269946502569,-0.00065009913700284333,-0.0006170408937114987,-0.00021456672492328779,0.00031084333580201325,0.00064249569393769548,0.00058432125927982944,0.00017670632506560437,-0.00033106160065040328,-0.00063318747201442647,-0.00055147958509512926,-0.00014035929313305253,0.00034906008499187145,0.00062229379442555236,0.00051862966112739323,0.00010556572070339705,-0.00036489563071504617,-0.00060993329170753205,-0.00048588008780987775,-7.2359154943202829e-05,0.00037862904370920261,0.00059622361612740463,0.00045333416438872047,4.076672890970808e-05,-0.00039032479973772846,-0.00058128116111209427,-0.00042108979150387078,-1.0809306511451116e-05,0.00040005074427624328,0.00056522078702242852,0.00038923938862606947,-1.7498358291909444e-05,-0.00040787778750602291,-0.00054815555449513127,-0.00035786982685983329,4.4147448554216722e-05,0.00041387959565617063,0.00053019646649758148,0.00032706237751102025,-6.9134898250785675e-05,-0.00041813227988439516,-0.00051145222016142644,-0.00029689267671199231,9.2463193679401549e-05,0.00042071408387955818,0.00049202896938229431,0.00026743070629513087,-0.00011414016306712218,-0.0004217050713564497,-0.00047203009909371394,-0.00023874079100788548,0.00013417875515284161,0.00042118681459727894,0.00045155601204410821,0.00021088161206897493,-0.00015259680756788012,-0.00041924208517313201,-0.00043070392882600249,-0.00018390623697621186,0.00016941680588133048,0.00041595454795340168,0.0004095677018271049,0.00015786216539023654,-0.00018466563421734998,-0.000411408459482276,-0.00038823764369306488,-0.00013279139083794607,0.00019837431838482975,0.00040568837176763244,0.00036680037081239796,0.00010873047790150323,-0.00021057776248908875,-0.00039887884249094926,-0.00034533866225445933,-8.5710654486384878e-05,0.00022131448001715901,0.00039106415260592512,0.00032393133451277177,6.375791869221706e-05,-0.00023062632040625087,-0.00038232803224969009,-0.00030265313232789057,-4.2893159746392137e-05,0.00023855819211644194,0.0003727533958429626,0.00028157463578629301,2.3132292399564845e-05,-0.00024515778323616681,-0.00036242208720544609,-0.00026076218381590645,-4.4864041268939551e-06,0.00025047528065009957,0.00035141463545969873,0.0002402778141235198,-1.3038085573268152e-05,-0.00025456308879629879,-0.00033981002244136248,-0.00022017921954614139,2.9439254537613362e-05,0.00025747554903095867,0.00032768546227587186,0.00020051972071601115,-4.471949675029469e-05,-0.00025926866060689758,-0.00031511619372217756,-0.00018134825486953833,5.8885331443888573e-05,0.00025999980425410918,0.00030217528582269484,0.00016270938056221616,-7.1947203356989689e-05,-0.00025972746932946832,-0.00028893345733587447,-0.00014464329798650062,8.3919275044191965e-05,0.0002585109854765904,0.00027545891036390667,0.00012718588452615976,-9.4819212158419198e-05,-0.00025641025970745914,-0.00026181717852333892,-0.00011036874512093067,0.00010466796264411082,0.00025348551978356218,0.000248070989940887,9.4219276957622648e-05,-0.00011348953079473805,-0.00024979706473747087,-0.00023428014529117166,-7.8760747950030861e-05,0.00012131074713729611,0.00024540502333520841,0.00022050141102728101,6.4012388418578696e-05,-0.00012816103511205769,-0.00024036912123650514,-0.00020678842788974746,-4.9989495333631214e-05,0.00013407217551617578,0.00023474845756350307,0.00019319163471435971,3.6703548442077042e-05,-0.00013907806967648068,-0.00022860129153961977,-0.00017975820749530587,-2.4162337556906404e-05,0.00014321450230828258,0.00022198483980907866,0.00016653201359685584,1.2370100252561542e-05,-0.00014651890500506923,-0.00021495508499414634,-0.00015355358094521892,-1.3276691767593674e-06,0.00014903012128730301,0.00020756659599202926,0.00014086008197169804,-8.9673718394782847e-06,-0.00015078817411855671,-0.0001998723604566344,-0.00012848533202013154,1.8520523716053447e-05,0.00015183403677270611,0.0001919236298524398,0.0001164598018749895,-2.7340200965652874e-05,-0.00015220940790836712,-0.00018376977740872303,-0.00010481064401259799,3.5437554322522508e-05,0.00015195649167526687,0.00017545816924270519,9.3561732125973162e-05,-4.2826288049981003e-05,-0.00015111778364293557,-0.00016703404886004732,-8.273371342503912e-05,4.9522472826279009e-05,0.00014973586330424308,0.00015854043518078703,7.2344073167586584e-05,-5.5544355112758862e-05,-0.00014785319386582336,-0.0001500180341786332,-6.2407210833393184e-05,6.0912163907792607e-05,0.00014551192999438139,0.00014150516416166191,5.2934527313616402e-05,-6.5647915786131976e-05,-0.00014275373414208186,-0.00013303769466331802,-4.3934522451167991e-05,6.9775219114973807e-05,0.00013961960202654153,0.00012464899885420772,3.5412902234267134e-05,-7.3319078326401687e-05,-0.00013614969779108602,-0.00011636991932810772,-2.7372694915852026e-05,7.63056991098989e-05,0.00013238319931956771,0.00010822874705973757,1.9814375305118448e-05,-7.876229536930054e-05,-0.00012835815412700998,-0.00010025121327778616,-1.2735996455325172e-05,8.0716898765850281e-05,0.00012411134619328722,9.2460493944213147e-05,6.1333279531218561e-06,-8.219817164252234e-05,-0.00011967817405194163,-8.4877226480735405e-05,-5.7466966513424757e-19,8.3235224095471629e-05,0.00011509254039052302,7.751953833529171e-05,-5.6723475348333285e-06,-8.3857435925784667e-05,-0.00011038675336263077,-7.0403086935861881e-05,1.0893911917825688e-05,8.4094284169493178e-05,0.00010559143975551558,6.3541110535935392e-05,-1.5676571041920137e-05,-8.397517686554369e-05,-0.00010073547010085498,-5.6944489415979588e-05,2.0033724435554231e-05,8.3529293681005044e-05,9.5845895760403489e-05,5.0621816867959487e-05,-2.3980132616547779e-05,-8.2785433969861485e-05,-9.0947897962923564e-05,-4.4579479356008813e-05,2.7531755609609077e-05,8.1771872797014485e-05,8.6064748714324529e-05,3.8821745215306794e-05,-3.0705591434758378e-05,-8.0516225412300953e-05,-8.1217783449575361e-05,-3.3350861223815493e-05,3.351951535914297e-05,7.9045320611162022e-05,7.6426385242831183e-05,2.8167156357238209e-05,-3.5992120686146112e-05,-7.7385083368906727e-05,-7.1707980341714135e-05,-2.3269152016994225e-05,3.8142561834154268e-05,7.5560427084861713e-05,6.7078044742841848e-05,1.8653678003681528e-05,-3.99904004323772e-05,-7.3595155721024809e-05,-6.2550121478900387e-05,-1.4315993495075376e-05,4.1555455133411947e-05,7.1511876067671668e-05,5.8135848242770808e-05,1.0249912277595197e-05,-4.2857655811372343e-05,-6.9331920315731234e-05,-5.3844994931911043e-05,-6.4479314739059533e-06,4.3916902781118346e-05,6.7075279063049921e-05,4.968551065624368e-05,2.9013630063843756e-06,-4.4752931638115274e-05,-6.4760544829009107e-05,-4.5663579715627797e-05,3.9953296291537202e-07,4.5385184280351504e-05,6.2404866099710255e-05,4.1783686018462905e-05,-3.4654133708561664e-06,-4.5832686633288954e-05,-6.0023911874249379e-05,-3.8048685381543165e-05,6.3077171177450281e-06,4.6113933556666898e-05,5.7631846631743368e-05,3.4459885122732225e-05,-8.9385301938381397e-06,-4.6246781367967525e-05,-5.5241315588944472e-05,-3.1017130332764293e-05,1.1370451789460097e-05,4.6248348372032483e-05,5.286344006972482e-05,2.7718896190273164e-05,-1.3616462092549847e-05,-4.6134923739573368e-05,-5.0507822760641412e-05,-2.4562385665406094e-05,1.5689792456732008e-05,4.5921885029704704e-05,4.8182562581375203e-05,2.1543631941913268e-05,-1.7603798599089426e-05,-4.5623624603112179e-05,-4.5894278855327099e-05,-1.8657604875447823e-05,1.9371837460259483e-05,4.5253485123502102e-05,4.3648144424166175e-05,1.5898320797233076e-05,-2.1007148330074762e-05,-4.4823704295580136e-05,-4.1447927310907659e-05,-1.3258954966925911e-05,2.2522738810224105e-05,4.4345368938411027e-05,3.9296040499209866e-05,1.0731955976730166e-05,-2.3931276151123861e-05,-4.3828378443691099e-05,-3.7193599362302222e-05,-8.3091614102569097e-06,2.524498446391039e-05,4.3281417619577972e-05,3.5140486243286357e-05,5.9819140645991619e-06,-2.6475548270073859e-05,-4.2711938872366331e-05,-3.3135421659745654e-05,-3.7411780521827705e-06,2.763402281123596e-05,4.212615363081324e-05,3.1176041579613146e-05,1.5776541104088924e-06,-2.8730751499825938e-05,-4.1529032871431321e-05,-2.9258980192346208e-05,5.1810653846835338e-07,2.9775290848442995e-05,4.0924316557847335e-05,2.7379957579601154e-05,-2.555590417143041e-06,-3.077634317147254e-05,-4.0314531763522918e-05,-2.5533871672840615e-05,4.5442127322413422e-06,3.1741697307494257e-05,3.9701019204988055e-05,2.3714893871837965e-05,-6.493211618646389e-06,-3.2678177565162072e-05,-3.9083967872404766e-05};
Convolution convo;
HPF::HPF(){
    convo.attach( &kernel);
}
int HPF::run(){
    return convo.run();
}
