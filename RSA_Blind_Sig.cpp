#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <functional>
#include <array>
#include <stdlib.h>
using namespace std;
typedef long long int ll;
ll r;
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}
ll modInverse(ll a, ll m)
{
    a = a%m;
    for (ll x=1; x<m; x++)
       if ((a*x) % m == 1)
          return x;
}

ll random_coprime(ll n)
{
    vector<ll> coprimes;
    for(ll i=2;i<n;i++)
    {
        if(gcd(i,n)==1)
        {
            coprimes.push_back(i);
        }
    }
    return coprimes[rand()%coprimes.size()];
}
/*2. Выбор сообщения(число) и соли(число).*/
ll blinding(ll m,ll n,ll e)
{
    cout << "Введите соль ";
    cin >> r;
   
    ll blinding_factor=1;
    while(e>0)
    {
        blinding_factor=(blinding_factor*r)%n;
        e--;
    }
    cout << "Ослепляющий фактор: " << blinding_factor << endl;
    return (m*blinding_factor)%n;
}
ll signing(ll m,ll n, ll d)
{
    ll blinding_signature=1;
    while(d>0)
    {
        blinding_signature=(blinding_signature*m)%n;
        d--;
    }
    return blinding_signature;
}
ll rsa_signature(ll blinded_signature, ll r,ll n)
{
    ll rsa_sign=(blinded_signature*modInverse(r,n))%n;
   // cout << modInverse(r,n) << endl;
    return rsa_sign;
}
vector<ll> primeFactors(int n)
{
    vector<ll> prime_factors;
    while (n%2 == 0)
    {
        prime_factors.push_back(2);
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        while (n%i == 0)
        {
            prime_factors.push_back(i);
            n = n/i;
        }
    }
    if (n > 2)
        prime_factors.push_back(n);
    return prime_factors;
}
ll crt(ll l, ll m,ll n)
{
    vector<ll> prime_fact=primeFactors(n);
    vector<ll> N,y,a,x_coe,k;
    for(ll i=0;i<prime_fact.size();i++)
    {
        N.push_back(n/prime_fact[i]);
    }
    for(int i=0;i<prime_fact.size();i++)
    {
        y.push_back(modInverse(N[i],prime_fact[i]));
    }
    for(int i=0;i<prime_fact.size();i++)
    {
        x_coe.push_back(l%prime_fact[i]);
    }
    for(int i=0;i<prime_fact.size();i++)
    {
        k.push_back(m%prime_fact[i]);
    }
    for(int i=0;i<prime_fact.size();i++)
    {
        a.push_back((modInverse(x_coe[i],prime_fact[i])*k[i])%prime_fact[i]);
    }
    ll ans=0;
    for(int i=0;i<prime_fact.size();i++)
    {
        ans+=(a[i]*N[i]*y[i]);
    }
    return ans%n;
}
int main()
{    /*ДАЩА ВОТ ТАКОЙ КОД БЫЛ БЫЛА ОШИБКА В РАНДОМ ПРАЙМ*/
    
    /*ll p, q;
    srand(time(NULL));
    p=random_prime(100);
    q=random_prime(100);
    while(p==q)
    {
        q=random_prime(100);
    }
    */

    setlocale(LC_ALL, "Russian");
    int q, p;
    q = 7;
    p = 5;
   // p=5;q=7;
    cout << "p=" << p << " q=" << q << endl;
    ll n=p*q;
    cout << "n=" << n << endl;
    ll phin=(p-1)*(q-1);
    cout << "phin=" << phin << endl;
    ll e=random_coprime(phin);
    //e=5;
    cout << "e=" << e <<endl;
    ll d=modInverse(e,phin);
    cout << "d=" << d << endl;
    /*2. Выбор сообщения(число) и соли(число).*/
    ll m;
    cout << "Введите сообщение ";
    cin >> m;
    /*3. Засаливание сообщения  использование соли и открытого ключа*/
    hash<ll> ll_hash;
   // cout << "Hashed value of " << m << " is " << ll_hash(m)<< endl;
    ll blind_msg = blinding(ll_hash(m),n,e);
    cout << "Слепое сообщение " << blind_msg << endl;
    ll blinded_signature=signing(blind_msg,n,d);
    /*.4. Вычисление подписи к засоленному сообщению с использованием секретного ключа (RSA).*/
    cout << "Слепая подпись " << blinded_signature << endl;
    /*.5. Вычисление подписи к засоленному сообщению с использованием секретного ключа (RSA).*/
    ll rsa_sign=rsa_signature(blinded_signature,r,n);
    cout << "RSA подпись " << rsa_sign << endl;

    ll k=e,msg=1;
    while(k>0)
    {
        msg=(msg*rsa_sign)%n;
        k--;
    }
    /*.7. Проверка правильности подписи с использованием открытого ключа (RSA)..*/
    cout << "Хэш сообщение=" << msg << endl;
    if(msg==ll_hash(m))
        cout << "действительное сообщение" << endl;
    else
        cout << "Недействительное сообщение" << endl;
    
}
