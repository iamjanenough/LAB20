#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

class Equipment{
    int hpmax;
    int atk;
    int def;
public:
    Equipment(int h,int a,int d){
        hpmax=h;
        atk=a;
        def=d;
    }

    vector<int> getStat(){
        return {hpmax,atk,def};
    }
};

class Unit{
    string name;
    string type;
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on;
    Equipment *equipment;

public:

    Unit(string t,string n){
        type=t;
        name=n;

        if(type=="Hero"){
            hpmax=rand()%20+120;
            atk=rand()%5+14;
            def=rand()%3+9;
        }
        else{
            hpmax=rand()%20+250;
            atk=rand()%5+25;
            def=rand()%3+5;
        }

        hp=hpmax;
        guard_on=false;
        dodge_on=false;
        equipment=NULL;
    }

    void newTurn(){
        guard_on=false;
        dodge_on=false;
    }

    int beAttacked(int oppatk){
        int dmg=0;

        if(oppatk>def)
            dmg=oppatk-def;

        if(guard_on)
            dmg/=3;

        if(dodge_on){
            if(rand()%2==0)
                dmg=0;
            else
                dmg*=2;
        }

        hp-=dmg;
        if(hp<0) hp=0;

        return dmg;
    }

    int attack(Unit &opp){
        return opp.beAttacked(atk);
    }

    int ultimateAttack(Unit &opp){
        return opp.beAttacked(atk*2);
    }

    int heal(){
        int h=rand()%21+10;
        if(hp+h>hpmax)
            h=hpmax-hp;

        hp+=h;
        return h;
    }

    void guard(){
        guard_on=true;
    }

    void dodge(){
        dodge_on=true;
    }

    bool isDead(){
        return hp<=0;
    }

    void equip(Equipment *eq){
        if(equipment!=NULL){
            vector<int> old=equipment->getStat();
            hpmax-=old[0];
            atk-=old[1];
            def-=old[2];
        }

        equipment=eq;

        vector<int> stat=equipment->getStat();
        hpmax+=stat[0];
        atk+=stat[1];
        def+=stat[2];

        if(hp>hpmax)
            hp=hpmax;
    }
};
