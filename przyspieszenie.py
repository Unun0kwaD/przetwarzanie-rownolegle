

# seq=[1104.710206,1188.191774,1365.889655,1434.033659,1511.600438,1613.480995,1706.688171,1854.374484,1918.766334,1974.093134,2064.606392]
# omp=[866.166038,888.429554,890.496786,907.661120,925.032254,897.274115,987.849462,961.452739,1028.745027,1045.360548,1052.930017]
# ocl=[517.712918,693.501408,557.103263,571.076339,564.563080,531.554622,579.563941,540.220459,606.464220,570.631171,582.740463]
# n=[10,11,12,13,14,15,16,17,18,19,20]

# for i in range(len(seq)):
#     print(str(seq[i]/omp[i])+" | "+str(seq[i]/ocl[i]))
    
        
l=[1.2754023565167767,1.3374068530817917,1.5338513024122244,1.5799218754682365,1.6341056557364106,1.798202988392237,1.7276804175654852,1.9287214116512075,1.8651524757261355,1.8884327878805693,1.9608201482207344]

n=[0.10970366315589027,0.5920694819754752,0.9609629030401876,1.2899707538983212,1.698590824943813,2.0254672235104523,2.3755417552557088,2.7147753887080284,2.911743232179114,2.949740897170135,3.105945996267728,3.1482754649733944,3.2695689679331834,3.3567737166169103,3.3715089400207545]
for i in range(len(n)):
    print(str(n[i]/6)+" |")
    
# # '''
# | 10 | 1104.710206 | 866.166038 | 517.712918 |1.2754023565167767 | 2.1338277790472286|0.21256705941946277 |
# | 11 | 1188.191774 | 888.429554 | 693.501408 |1.3374068530817917 | 1.7133227997714462|0.22290114218029863 |
# | 12 | 1365.889655 | 890.496786 | 557.103263 |1.5338513024122244 | 2.4517710552343326|0.2556418837353707 |
# | 13 | 1434.033659 | 907.661120 | 571.076339 |1.5799218754682365 | 2.5111067664107862|0.2633203125780394 |
# | 14 | 1511.600438 | 925.032254 | 564.563080 |1.6341056557364106 | 2.6774695185522934|0.2723509426227351 |
# | 15 | 1613.480995 | 897.274115 | 531.554622 |1.798202988392237 | 3.035400179438191|0.29970049806537286 |
# | 16 | 1706.688171 | 987.849462 | 579.563941 |1.7276804175654852 | 2.9447797736609016|0.2879467362609142 |
# | 17 | 1854.374484 | 961.452739 | 540.220459 |1.9287214116512075 | 3.4326254274646044|0.3214535686085346 |
# | 18 | 1918.766334 | 1028.745027 | 606.464220 |1.8651524757261355 | 3.163857439108279|0.3108587459543559 |
# | 19 | 1974.093134 | 1045.360548 | 570.631171 |1.8884327878805693 | 3.459490533159115|0.3147387979800949 |
# | 20 | 2064.606392 | 1052.930017 | 582.740463 |1.9608201482207344 | 3.542926093326731|0.32680335803678906 |

# # ''' 

# '''
| 100 | 53.061218 | 483.677723 | 481.176915 |0.10970366315589027 | 0.11027382309061938|0.018283943859315043 |
| 200 | 259.070173 | 437.567179 | 452.757588 |0.5920694819754752 | 0.5722050383394127|0.09867824699591253 |
| 300 | 560.994260 | 583.783472 | 538.884535 |0.9609629030401876 | 1.0410286871565169|0.16016048384003126 |
| 400 | 999.536843 | 774.852329 | 518.104657 |1.2899707538983212 | 1.9292180247667607|0.2149951256497202 |
| 500 | 1576.605983 | 928.184681 | 575.924931 |1.698590824943813 | 2.7375199407715862|0.28309847082396883 |
| 600 | 2326.188407 | 1148.470032 | 600.362327 |2.0254672235104523 | 3.8746408666645067|0.3375778705850754 |
| 700 | 3164.366317 | 1332.060912 | 761.962001 |2.3755417552557088 | 4.152918797587126|0.3959236258759515 |
| 800 | 4136.986050 | 1523.877838 | 971.705300 |2.7147753887080284 | 4.2574493007293475|0.4524625647846714 |
| 900 | 5318.353073 | 1826.518566 | 1300.059495 |2.911743232179114 | 4.090853605895936|0.485290538696519 |
| 1000 | 6455.107299 | 2188.364173 | 1414.820949 |2.949740897170135 | 4.562490613078984|0.49162348286168917 |
| 1100 | 7830.048386 | 2520.986648 | 1483.100933 |3.105945996267728 | 5.279511469365383|0.5176576660446214 |
| 1200 | 9257.223421 | 2940.410877 | 1422.353262 |3.1482754649733944 | 6.5083855525337135|0.5247125774955658 |
| 1300 | 10923.482497 | 3340.954910 | 1528.955928 |3.2695689679331834 | 7.14440638670914|0.5449281613221972 |
| 1400 | 12812.112596 | 3816.793647 | 1461.046033 |3.3567737166169103 | 8.76913684211071|0.5594622861028183 |
| 1500 | 14774.436425 | 4382.143630 | 1993.216026 |3.3715089400207545 | 7.412360844122572|0.5619181566701258 |



# '''