import subprocess
import matplotlib.pyplot as plt
import time

if __name__ == '__main__':
    
    time_measure_m = []
    time_measure_p = []
    time_measure_g = []
    num_measure = []
    # n=500
    amount=50
    folder="/home/pawelm/Semestr_6/Przetwarzanie_rownoległe/projekt/"
    print('^ '+'$n$'+' ^ '+'czas [s]'+ ' ^')
    l=15
    for n in range(100,1600,100):
        start = time.time()
        m = subprocess.Popen(['./bin/main',folder+str(n)+"-"+str(l)+"-"+str(amount)],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        p = subprocess.Popen(['./bin/parallel_cpu',folder+str(n)+"-"+str(l)+"-"+str(amount)],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        g = subprocess.Popen(['./bin/parallel_gpu',folder+str(n)+"-"+str(l)+"-"+str(amount)],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        eend = time.time()
        answer_m=  m.communicate('')[0]
        answer_p=  p.communicate('')[0]
        answer_g=  g.communicate('')[0]
        
        time_m= answer_m.decode(encoding='utf-8').strip()
        time_p= answer_p.decode(encoding='utf-8').strip()
        time_g= answer_g.decode(encoding='utf-8').strip()
        
        # time_passed= str((end-start)*1000*1000*10)
        # time_measure= answer.decode(encoding='utf-8').strip()
        print('| '+str(n)+' | '+ time_m+' | '+time_p+' | '+time_g+' |')
        time_measure_m.append(float(time_m))
        time_measure_p.append(float(time_p))
        time_measure_g.append(float(time_g))
        num_measure.append(n)
        
    # create plot with n and time
    plt.figure(1)
    plt
    plt.title('Czas wykonania algorytmu w zależności od n')
    
    plt.plot(num_measure,time_measure_m,'r',label='Sekwencyjnie')
    plt.plot(num_measure,time_measure_p,'b',label='OpenMP')
    plt.plot(num_measure,time_measure_g,'g',label='OpenCL - GPU')
    plt.legend(loc='upper left')
    plt.xlabel('n')
    plt.ylabel('czas [ms]')
    plt.savefig('wykres1.png',dpi=300)
    plt.show()
        

