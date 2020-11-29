import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

files = ["philosophers","proco","reawri"]
titles = ["Problème des philosophes","Système producteurs-consommateurs","Problème des lecteurs et écrivains"]

# Making graphs for each solution
for i in range(len(files)):
    tab=[[],[],[]]
    # Grabbing values for various lock implementations
    tab[0]=pd.read_csv("./data/"+files[i]+".csv").values
    tab[1]=pd.read_csv("./data/"+files[i]+"_tas.csv").values
    tab[2]=pd.read_csv("./data/"+files[i]+"_tatas.csv").values
    c = ["orange","lightblue","lightgreen"]
    label = ["Classique","TAS","TATAS"]

    ######## Boxplots
    box=[]
    for j in range(len(tab)):
        box.append(plt.boxplot(np.transpose(tab[j])[1:],notch=True,patch_artist=True,
            boxprops=dict(facecolor=c[j], color=c[j]),
            capprops=dict(color=c[j]),
            whiskerprops=dict(color=c[j]),
            flierprops=dict(color=c[j], markeredgecolor=c[j]),
            medianprops=dict(color=c[j]))["boxes"][0])
    plt.title(titles[i])
    plt.xticks([i+1 for i in range(0,len(np.transpose(tab[j])[0]))],np.arange(np.transpose(tab[j])[0][0],np.transpose(tab[j])[0][-1]+1,step=1).astype("int"))
    plt.ylim(bottom=0)
    plt.xlabel("Nombre de threads")
    plt.ylabel("Temps écoulé [s]")
    plt.legend(box,label,loc="best")
    #plt.show()
    plt.savefig('./graphs/'+files[i]+'.png', bbox_inches='tight')
    plt.close()
    ####### End boxplots

    ####### Graphs with improved readability
    for j in range(len(tab)):
        plt.plot(np.transpose(tab[j])[0],[ np.mean(tab[j][k][1:]) for k in range(len(tab[j]))],color=c[j],label=label[j]+" temps moyen")
        plt.fill_between(np.transpose(tab[j])[0],[np.max(tab[j][k][1:]) for k in range(len(tab[j]))],[np.min(tab[j][k][1:]) for k in range(len(tab[j]))],label=label[j]+" extrêmes",alpha=.3,color=c[j])
    plt.title(titles[i])
    plt.ylim(bottom=0)
    plt.xticks(np.arange(np.transpose(tab[j])[0][0],np.transpose(tab[j])[0][-1]+1,step=1))
    plt.xlim(right=np.transpose(tab[j])[0][-1])
    plt.xlabel("Nombre de threads")
    plt.ylabel("Temps écoulé [s]")
    plt.grid(color='gray', alpha=.2, linestyle='-', linewidth=.5)
    plt.legend(loc="best")
    plt.savefig('./graphs/'+files[i]+'_alt.png', bbox_inches='tight')
    plt.close()
    ####### End graphs with improved readability


#######
# Spinlock perf graphs
#######
tab=[[],[],[]]

# Grabbing values for various lock implementations
tab[1]=pd.read_csv("./data/tas.csv").values
tab[2]=pd.read_csv("./data/tatas.csv").values
tab[0]=pd.read_csv("./data/btatas.csv").values
c = ["orange","lightblue","lightgreen"]
label = ["BTATAS","TAS","TATAS"]

######## Boxplots
box=[]
for j in range(len(tab)):
    box.append(plt.boxplot(np.transpose(tab[j])[1:],notch=True,patch_artist=True,
        boxprops=dict(facecolor=c[j], color=c[j]),
        capprops=dict(color=c[j]),
        whiskerprops=dict(color=c[j]),
        flierprops=dict(color=c[j], markeredgecolor=c[j]),
        medianprops=dict(color=c[j]))["boxes"][0])
plt.title("Spinlocks performances")
plt.ylim(bottom=0)
plt.xlabel("Nombre de threads")
plt.ylabel("Temps écoulé [s]")
plt.legend(box,label,loc="best")
plt.savefig('./graphs/spinlock.png', bbox_inches='tight')
plt.close()
######## End Boxplots


####### Graphs with improved readability
for j in range(len(tab)):
    plt.plot(np.transpose(tab[j])[0],[ np.mean(tab[j][k][1:]) for k in range(len(tab[j]))],color=c[j],label=label[j]+" temps moyen")
    plt.fill_between(np.transpose(tab[j])[0],[np.max(tab[j][k][1:]) for k in range(len(tab[j]))],[np.min(tab[j][k][1:]) for k in range(len(tab[j]))],label=label[j]+" extrêmes",alpha=.3,color=c[j])
plt.title("Spinlocks performances")
plt.ylim(bottom=0)
plt.grid(color='gray', alpha=.2, linestyle='-', linewidth=.5)
plt.xlim(right=len(np.transpose(tab[j])[0]))
plt.xticks(np.arange(1,1+len(np.transpose(tab[j])[0]),step=1))
plt.xlabel("Nombre de threads")
plt.ylabel("Temps écoulé [s]")
plt.legend(loc="best")
plt.savefig('./graphs/spinlock_alt.png', bbox_inches='tight')
plt.close()
####### End graphs with improved readability
