#include <stdio.h>

int main(){

    int canal, totalSpec, spec, spec17, spec18, spec19, spec20, spec22;

    totalSpec=0;
    spec17=0;
    spec18=0;
    spec19=0;
    spec20=0;
    spec22=0;

    do{
    
        scanf("%d",&canal);
        if(canal!=0){
            scanf("%d",&spec);
            totalSpec=totalSpec+spec;
            if (canal==17)
                spec17=spec17+spec;
            if (canal==18)
                spec18=spec18+spec;
            if (canal==19)
                spec19=spec19+spec;
            if (canal==20)
                spec20=spec20+spec;
            if (canal==22)
                spec22=spec22+spec;
        }
            
    }while(canal!=0);
    
    if(spec17!=0)
        printf("17 %lf\n",100.0*spec17/totalSpec);
    if(spec18!=0)
        printf("18 %lf\n",100.0*spec18/totalSpec);
    if(spec19!=0)
        printf("19 %lf\n",100.0*spec19/totalSpec);
    if(spec20!=0)
        printf("20 %lf\n",100.0*spec20/totalSpec);
    if(spec22!=0)
        printf("22 %lf\n",100.0*spec22/totalSpec);
    
    return 0;
}
