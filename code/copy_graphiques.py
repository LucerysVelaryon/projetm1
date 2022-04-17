import numpy as np
import matplotlib 
import matplotlib.pyplot as plt

import os
myCmd1 = 'g++ __main__.cpp annexes.cpp grille.cpp joueur.cpp -o a'
myCmd2 = './a'

def afficheHisto_1data(data):   #Prend en argument 1 liste de scores
    gagnant = data[:,2]
    labels, counts = np.unique(gagnant, return_counts=True)
    plt.bar(labels, counts, align='center', color = "orange")
    #plt.hist(gagnant, color="orange", bins=3)

    plt.xticks([0, 1, 2],["Egalité", "Blanc", "Noir"])
    plt.title("Nombre de parties gagnées")   #add sur cb de parties ?
    print("Nombre d'égalité, de victoires de blanc, de victoires de Noir : ", counts)

def afficheHisto_moy(moy, std, N):   #Prend en argument une moyenne de scores
    plt.bar([0, 1, 2], moy, align='center', color = "orange")
    plt.xticks([0, 1, 2],["Egalité", "Blanc", "Noir"])
    plt.title("Nombre de parties gagnées")   #add sur cb de parties ?
    print("Nombre d'égalité, de victoires de blanc, de victoires de Noir en moyenne: ", moy)
    
    for i in range(3):
        plt.axhline(y = moy[i]+std[i], xmin=i*(1/3)+0.04, xmax=(i+1)*(1/3)-0.04, c='k', linestyle="dashed")
        plt.axhline(y = moy[i]-std[i], xmin=i*(1/3)+0.04, xmax=(i+1)*(1/3)-0.04, c='k', linestyle="dashed")
    plt.axhline(y = (N-moy[0])/2, xmin=0, xmax=3, c="darkred", linestyle="dashed")

def stats(N):    #fait une moyenne sur N listes du nb de victoires B/N
    print("Nombre de set de parties sur lequel on moyenne: ", N)
    nbVict = np.zeros((N,3))   # tableau du nb de vict pour chaque set de data 
    for i in range(N):         # (0 = egalité, 1 = blanc, 2 = noir)
        os.system(myCmd1)
        os.system(myCmd2)
        data = np.loadtxt("resultats.dat", delimiter = ' ')   #[scoreB, scoreN, gagnant]
        gagnant = data[:,2]
        nbVict[i][0] = np.sum(gagnant == 0)
        nbVict[i][1] = np.sum(gagnant == 1)
        nbVict[i][2] = np.sum(gagnant == 2)

    afficheHisto_moy(np.mean(nbVict, axis=0), np.std(nbVict, axis=0), N)
    #print(np.std(nbEgalite), np.std(nbVictB), np.std(nbVictN))

from scipy.optimize import curve_fit

def model(x, a, sigma, mu):
    return a * (1/(sigma*np.sqrt(2*np.pi))) * np.exp(- (x-mu)*(x-mu)/(2*sigma*sigma))

def gaussienne():      #affiche la distrib gaussienne du score de blanc
    N = 10000           #nbParties
    #os.system(myCmd1)
    #os.system(myCmd2)
    data = np.loadtxt("resultats.dat", delimiter = ' ')   #[scoreB, scoreN, gagnant]
    scoreBlanc = data[:,1]
    labels, counts = np.unique(scoreBlanc, return_counts=True)
    print(labels, counts)
    xdata = labels
    ydata = counts
    popt, pcov = curve_fit(model, xdata, ydata, p0 = (1,1,30))  #popt renvoie les paramètres optimisés
    print(*popt)
    x = np.linspace(np.min(labels),np.max(labels),1000)
    plt.scatter(xdata,ydata, s=1)
    plt.plot(x, model(x, *popt), c="orange")
    plt.xlabel("Score de blanc")
    plt.ylabel("Nombre de parties")
    

#os.system(myCmd1)
#os.system(myCmd2)

stats(10)