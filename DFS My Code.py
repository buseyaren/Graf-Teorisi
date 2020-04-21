# -*- coding: utf-8 -*-
"""
Created on Tue Apr 21 20:50:30 2020

@author: busetekin
"""

class GrafTeorisi:
    def __init__(self,Tepe): # Graf Oluşturma Başlangıç Fonksiyonu  
        self.Tepe = Tepe        # Tepelerin this ile gösterimi 
        self.komsu  = [[]for i in range(Tepe)]  # komşuluk listesi   başlangıçta tepelere atandı.
        
    def kenarEkle(self,Tepe, Tepe2):     #Tepe1 ve Tepe2 tepelerinin arasında kenar ekleme fonksiyonu
        self.komsu[Tepe].append(Tepe2)   #Komsuluk Listesine Tepelerin eklenmesi- komsu oldugu bilinerek
        
    def DFS(self,graf):          
  #Tüm tepelerin başlangıçta visited degerleri 0 varsayıldı.
        visited = [0 
                   for i in range(self.Tepe)
                   ]  
  
#DFS yapısı Stack ile kullanıldığı için içi boş bir stack yapısı oluşturuldu.
        stack = [] #push-pop çalışma mantığı
        stack.append(graf)   #stackteki değerw ilk tepe pushlanır. - push
      #stack içerisindeki değerlerin hepsi gezinene kadar pushlanan tepeler pop ile çıkartılır
        while (len(stack)):  
                # Pop a vertex from stack and print it  
                graf = stack[-1]  
                stack.pop() # pop
            #DFS arama algoritmasında olduğu gibi tepelerin ziyaret edilip edilmediği kontrol dilir.
                if (not visited[graf]):  
                    print(graf,end=' -> ') 
                    visited[graf] = 1 
      
           #gezilen tepeler eğer ziyaret edilmemiş ise stack'e ekleme yapılır.
                for dugum in self.komsu[graf]:  
                    if (not visited[dugum]):  
                        stack.append(dugum)  

yeniGraf = GrafTeorisi(6); 
yeniGraf.kenarEkle(0, 1);  
yeniGraf.kenarEkle(0, 2);  
yeniGraf.kenarEkle(1, 2);  
yeniGraf.kenarEkle(2, 3);  
yeniGraf.kenarEkle(3, 4); 
yeniGraf.kenarEkle(3, 5); 
yeniGraf.kenarEkle(4, 5); 
print("DFS Arama Algoritması : ")  
yeniGraf.DFS(0) 
  
  