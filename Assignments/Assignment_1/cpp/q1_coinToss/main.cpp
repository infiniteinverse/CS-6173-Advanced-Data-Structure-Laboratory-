#include<iostream>
#include<random>
#include<fstream>


void oneCoinToss(std::mt19937 generator){
    std::uniform_int_distribution<int> coin(0,1);
    int N = 5000;
    
    std::fstream file("oneCoinToss.csv", std::ios::out| std::ios::in | std::ios::trunc);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open the file!!");
    }
    file << "Toss,Heads,Tails,HeadProbability,TailProbability";
    file << "\n";
    
    int heads = 0, tails = 0;
    
    for(int i = 1; i <= N; i++){
        int result = coin(generator);
        if(result){
            heads++;
        }
        else tails++;
    
        double head_prob = heads*1.0/i;
        double tail_prob = tails*1.0/i;
        
        file << i << ", " << heads << ", "
        << tails << ", " << head_prob << ", " << tail_prob << "\n";
    }
    file.close();
    std::cout<<heads << " " << tails << " " <<heads*1.0/N << " " << tails*1.0/N << std::endl;
    
}

void twoCoinToss(std::mt19937 generator){
    std::uniform_int_distribution<int> coin(0,1);

    int N = 5000;
    
    std::fstream file("twoCoinToss.csv", std::ios::out| std::ios::in | std::ios::trunc);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open the file!!");
    }
    file << "Toss,HH,HT,TH,TT,P(HH),P(HT),P(TH),P(TT)";
    file << "\n";
    
    int HH = 0, HT = 0, TH = 0, TT = 0;
    
    for(int i = 1; i <= N; i++){
        int result1 = coin(generator);
        int result2 = coin(generator);
        if(result1){
           if(result2){
                HH++;
           } 
           else HT++;
        }
        else{
            if(result2){
                TH++;
            }
            else TT++;
        }
    
        double HH_prob = HH*1.0/i;
        double HT_prob = HT*1.0/i;
        double TH_prob = TH*1.0/i;
        double TT_prob = TT*1.0/i;
        
        file    << i << ", " << HH << ", " << HT << ", " << TH << ", " << TT << ", " 
                << HH_prob << ", " << HT_prob << ", " << TH_prob << ", " << TT_prob << "\n";
    }
    file.close();

    std::cout<<HH << " " << HT << " " << TH << " " << TT << " " << HH*1.0/N << " " << HT*1.0/N << " " <<TH*1.0/N << " "<<TT*1.0/N << "\n";

}
int main(){
    std::random_device rd;
    std::mt19937 generator(
    static_cast<unsigned int>(rd())
    );

    // Experiment with single coin toss;
    oneCoinToss(generator);
    
    // Experiment with 2 coin tosses;
    twoCoinToss(generator);


    return 0;
    
}
