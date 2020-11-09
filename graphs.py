import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

files = ["philosophers","proco","reawri"]
titles = ["Problème des philosophes","Système producteurs-consommateurs","Problème des lecteurs et écrivains"]

for i in range(len(files)):
    tab=pd.read_csv(files[i]+".csv").values
    p = plt.boxplot(np.transpose(tab)[1:],0,'+',patch_artist=True)
    plt.title(titles[i]);
    plt.xlabel("Nombre de threads");
    plt.ylabel("Temps écoulé [s]");
    #plt.show()
    plt.savefig(files[i]+'.png', bbox_inches='tight')
    plt.close()
