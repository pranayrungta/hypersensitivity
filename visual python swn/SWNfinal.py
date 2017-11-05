import random as cfr
from visual import *
radi=7


#-----------------------------------------------------------------------------------------------
class Node(object):

    def __init__(self,  value=0,  nb=[0,0],  a=0, isRandom=False,  nodeNumber=0,    totalN=2 ):
        self._value = value       #value at a node
        self._nb   = nb    #array of neighbours
        self.a     = a            #a at a the site
        self.isRandom   = isRandom    #status whether a node is random
        self.nodeNumber = nodeNumber
        self.totalN     = totalN



        #******sphere and arrow initialization************
        a= (2*3.14*self.nodeNumber)/self.totalN
        
        self._pos= radi*vector(cos(a),sin(a),0)
        self._sph=sphere(pos=self._pos, radius=.2)

        self._cur=[]
        z=0
        for i in self._nb:
            angon= (2*3.14/self.totalN)*i
            rf = radi *  vector(cos(angon),sin(angon),0)
            ad=.02
            if i>self.nodeNumber:
                m= (0.5+ad)*(rf+self._pos)
            else:
                m= (0.5-ad)*(rf+self._pos)
            self._cur += [ curve(  pos= [self._pos,m, rf], radius=0.05 ) ]
            z+=1
        #******color initialization************
        r,g,b=0,0,0
        if value > 0:
            r=value/2.0 + 0.5
        else :
            g=-(value/2.0)+0.5
        self._sph.color = (r,g,b)
        for i in self._cur:
            i.color = (r,g,b)
        #***************************************

    
    #------sets position------------    
    @property
    def pos(self):
        return self._pos

    @pos.setter
    def pos(self, value):
        self._sph.pos=value
        for i in self._cur:
            i.pos[0]=value
            ad=.02
            if i>self.nodeNumber:
                m= (0.5+ad)*(i.pos[2]+self._pos)
            else:
                m= (0.5-ad)*(i.pos[2]+self._pos)
            i.pos[1]=m
        self._pos = value
    #-------------------------------

    #-----sets neighbour array-----------
    @property
    def nb(self):
        return self._nb

    @nb.setter
    def nb(self, value):

        self._nb = value

        for i in self._cur:
            i.visible= False
            del i

        self._cur=[]
        z=0
        for i in self._nb:
            angon= (2*3.14/self.totalN)*i
            rf = radi *  vector(cos(angon),sin(angon),0)
            ad=.02
            if i>self.nodeNumber:
                m= (0.5+ad)*(rf+self._pos)
            else:
                m= (0.5-ad)*(rf+self._pos)
            self._cur += [ curve(  pos= [self._pos,m, rf], radius=0.05 ) ]
            z+=1
        self.value = self._value
    #--------------------------------------
    #-----sets value-----------------------
    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value
        r,g,b=0,1,0
        if value > 0:
            r=value/2.0 + 0.5
        else :
            g=-(value/2.0)+0.5
        self._sph.color = (r,g,b)
        for i in self._cur:
            i.color = (r,g,b)
    #--------------------------------------
            
#---------------------------------------------------------------------------------------------


#------------------Parameters--------------------------
n=20    #No of sites
et= 5    #evolution time
dt=.01   #time steps

a0=0    #a for random links
a1=1    #a for regular links

p=0.6    #probablity of a link to go random
k=1     #No of neighbours on each side for regular points
kr=2  #No of neighbours for random points

couple= [1] # coupling constant
bias = [.1,.5,1] # global bias

#--------------------------------------------------------

#---------------------Initializing------------------

node = []

# initialising nb
for i in range(n):
    
    r=cfr.random()
    if r>p:
        #regular neighbours
        z=0
        #ion - index of neighbours
        ion=range(-k,k+1)
        ion.remove(0)
        index=[]
        for j in ion:
            index += [(i+j)%n]
            z+=1

        node += [ Node(nb =index , totalN=n, nodeNumber =i , a=0 , value = (2*cfr.random()-1)) ]
        
    else:
        #site with random neighbours

        s= range(n)
        s.remove(i)
        s= cfr.sample(s,kr)

        node += [ Node( isRandom=True, nb =s , totalN=n, nodeNumber =i , a=1 , value = (2*cfr.random()-1) ) ]

#----------------------------------------------------

#---------Writing to file----------------------
nfile = open('connection array.txt','w')
for i in range(n):

    nfile.write( '%s\t-\t'%i )
    #assign neighbours to i
    for j in node[i].nb:
            nfile.write( '%s\t'%j )
    if node[i].isRandom:
        nfile.write( ' random site\n' )
    else:
        nfile.write( ' regular site\n' )
nfile.close()
#-----------------------------------------------
