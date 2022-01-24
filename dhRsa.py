import random

def gcd(a,b):
        while b != 0:
            a, b = b, a % b
        return a
    
def isCoprime(x, y):
    return gcd(x, y) == 1

class DH:
    def primeRoots(number):
        roots = []
        required_set = set(num for num in range (1, number) if gcd(num, number) == 1)

        for g in range(1, number):
            actual_set = set(pow(g, powers) % number for powers in range (1, number))
            if required_set == actual_set:
                roots.append(g)      
        return roots
        
    def calculate(self):
        print("DH")
        n = 227
        print('n = %d'%(n))        
        g = 211
        print('g = %d'%(g))
        x = random.randint(999999,99999999)
        print('Klucz prywatny A, x = %d'%(x))
        X = int(pow(g,x,n)) 
        y = random.randint(999999,99999999)
        print('Klucz prywatny B, y = %d'%(y))
        Y = int(pow(g,y,n)) 
        ka = int(pow(Y,x,n))
        kb = int(pow(X,y,n))
        print('Klucz sesji a, k = %d'%(ka))
        print('Klucz sesji b, k = %d'%(kb))

class RSA: 
    def calculate(self):
        print("RSA")
        p = 31
        print('p = %d'%(p))
        q = 19
        print('q = %d'%(q))
        n = p * q
        print('n = %d'%(n))
        phi=(p - 1) * (q - 1)
        print('phi = %d'%(phi))
        counter = 0
        x = 0
        tab=[1]
        while x < phi:
            x += 1
            if(isCoprime(x, phi)):
                tab.append(x)
                counter+=1
        e = random.choice(tab)
        print('e = %d'%(e))
        d = pow(e, -1, phi)
        print('d = %d'%(d))
        
        message = 1947
        c = (message ** e) % n
        print(f'Encode: message = {message}, c = {c}')
        
        m = (c ** d) % n
        print(f'Decode: message = {message}, c = {c}')
        
if __name__=='__main__':
    d = DH()
    d.calculate()
    r = RSA()
    r.calculate()