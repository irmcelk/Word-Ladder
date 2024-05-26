#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bu projede kelime merdiveni oyunu yapilmistir. Kullanýcýnýn girdigi kaynak kelime ve hedef kelime dictionary dosyasýnda bulunmalýdýr. Kaynak kelimeden 
birer harf degistirerek hedef kelimeye gitmeye calisilmaktadir. Bu algoritmada gidilen kelimelerde stacklerde tutulur. Stackler ise queue yapisinda tutulmaktadir.
1 harf farkli tum kelimeler bulunduktan sonra queuenin frontundaki stack dequeue edilir bu stack kopyalanir ve stackin top elemaninin 1 harf fakli oldugu kelimeler bulunarak 
kopyalanan stack ustune eklenir ve bu stackler de queue yapisina eklenir. Kelime bulunana kadar veya queue yapisi bosalana kadar arama devam eder.
*/

#define MAX_SIZE 100000 //queue kapasitesi
#define LENGTH 100 //kelime uzunlugu

//@brief Stack yapisi
struct Stack{
	char* items[LENGTH]; //stackteki kelimeler
	int top; //stackteki eleman sayisi
};

//@brief Circular queue yapisi
struct Queue{
    struct Stack* stacks[MAX_SIZE]; //queueye eklenen stackler
	int front; 
	int rear; 
};


/*@brief Stack olusturma
@return return olusturulan stack
*/
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

/* @brief Queue'nin baþlangýç durumu
  @param olusturulmus queue 
*/
void initializeQueue(struct Queue* queue){
 queue->front=queue->rear=-1; //circular queue 
}

/*@brief Stack'e eleman eklemek
@param1 kelime eklenecek stack
@param2 stacke eklenecek kelime
*/
void pushStack(struct Stack* stack, char* item) {
    if (isFullStack(stack)) //stackin dolu olup olmadigi kontrolu
	{
        printf("Stack dolu, eleman eklenemiyor.\n");
        return;
    }
    stack->top++; //stackin son elemanýný gosteren top arttilir
    stack->items[stack->top] = strdup(item);//stackin en ustundeki yere kelime eklenir
}

/*@brief Stack'ten eleman çýkarmak
 @param eleman cikarilacak stack
 @return cikarilan eleman
*/
char* popStack(struct Stack* stack) {
    if (isEmptyStack(stack))//stackin bos olup olmadigi kontrolu
	{
        printf("Stack boþ, eleman çýkarýlamýyor.\n");
        return NULL;
    }
    char* item = stack->items[stack->top];
    stack->top--;//stackin son elemanýný gosteren top azaltilir
    return item;
}


/*@brief Yýðýnýn boþ olup olmadýðýný kontrol etmek
@param bos olup olmadigi kontrol edilen stack
@return stack bossa 1, degilse 0
*/
int isEmptyStack(struct Stack* stack) {
    return (stack->top == -1);
}

/*@brief Yýðýnýn dolu olup olmadýðýný kontrol etmek
@param dolu olup olmadigi kontrol edilen stack
@return stack doluysa 1, degilse 0
*/
int isFullStack(struct Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}
 
/*@brief Stack'in tüm elemanlarýný yazdýrmak
@param yazdirilan stack
*/
void displayStack(struct Stack* stack) {
	int i;
    printf("---------\n");
    for ( i = stack->top; i >= 0; i--) {
        printf("|%s|\n", stack->items[i]);
    }
    printf("---------\n");
}

/*@brief Kuyrugun bos olup olmadýðýný kontrol etmek
@param bos olup olmadigi kontrol edilen queue
@return queue bossa 1, degilse 0
*/
int isEmptyQueue(struct Queue* q) {
    return (q->front == -1);
}

/*@brief Kuyrugun dolu olup olmadýðýný kontrol etmek
@param dolu olup olmadigi kontrol edilen queue
@return queue doluysa 1, degilse 0
*/
int isFullQueue(struct Queue* q) {
    return (q->front == 0 && q->rear == MAX_SIZE - 1) || (q->rear == (q->front - 1) % (MAX_SIZE - 1));
}


/*@brief Kuyruga stack eklemek
@param1 stack eklenecek queue
@param2 queueya eklenecek stack
@return stack eklenirse 1,eklenemezse 0
*/
int enqueue(struct Queue *q,struct Stack *s){
if(isFullQueue(q)){

    return 0;
}

    if(isEmptyQueue(q)){
    q->front=0;
    }

    q->rear=(q->rear+1)%MAX_SIZE;
    q->stacks[q->rear]=s;

return 1;
}


/*@brief Kuyruga stack cýkartmak
@param1 stack cýkartýlacak queue
@return stack cýkartýlýrsa stack ,eklenemezse NULL
*/
struct Stack* dequeue(struct Queue *q){
  if(isEmptyQueue(q)){
    return NULL;
  }
  struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack=q->stacks[q->front];
    q->front=(q->front+1)%MAX_SIZE;
    printf("Cikarilan stack\n");
    displayStack(stack);
  return stack;
}


/*@brief Kuyrugu yazdirmak
@param1 yazdirilacak queue
*/
void printQueue(struct Queue *q) {
    int i = q->front;
    int j;
    if (isEmptyQueue(q)) {
        printf("Kuyruk bos.\n");
        return 0;
    }
    printf("Kuyruk elemanlari: \n");
    do {
        printf("Stack %d:\n", i);
        struct Stack* current_stack = q->stacks[i];
        for (j = current_stack->top; j >= 0; j--) {
            printf("|%s|\n", current_stack->items[j]);
        }
        printf("---------\n");
        i = (i + 1) % MAX_SIZE;
    } while (i != (q->rear + 1) % MAX_SIZE);
}


/*@brief kelimeleri karsilastirip farkli harf sayisi 1 olanlari bulur
@param1 1.kelime
@param2 2.kelime
@return kelime uzunluklari farkliysa ya da harf farki 1den fazlaysa -1 degilse farkli harf sayisi return edilir 
*/
int compareWords(const char *kelime1, const char *kelime2) {
    int count = 0; //farkli harf sayisi
    int i;
    int uzunluk = strlen(kelime1);
    if (uzunluk != strlen(kelime2))
        return -1; // Kelimelerin uzunluklarý ayný deðilse  çýk

    for (i = 0; i < uzunluk; i++) {
        if (kelime1[i] != kelime2[i])
            count++;
        if (count > 1)
            return -1; // 1'den fazla farklý harf varsa hemen çýk
    }

    return count;
}

/*@brief Stacki kopyalama islemi
@param1 kopyalanacak stack
@return kopyalanan stack
*/
struct Stack* copyStack(struct Stack* mainStack) {
    struct Stack* copy = createStack(); // Yeni bir yigin olustur
    struct Stack* tempStack = createStack(); // Geçici bir yigin olustur

    // Orijinal stacki gecici stacke kopyala
    while (mainStack->top != -1) {
        pushStack(tempStack, popStack(mainStack));
    }

    // Gecici stacke orijinal stacke ve kopya stacke kopyala
    while (tempStack->top != -1) {
        char* item = popStack(tempStack);
        pushStack(mainStack, item); // Orijinal stacki geri kopyala
        pushStack(copy, item); // Kopya stacki kopyala
    }

    // Gecici stacki sil
    free(tempStack);

    return copy;
}


/*@brief Stacke ayni kelimeleri eklememek icin fakat addWordFile zaten kullanýlan tüm kelimeleri kaydediyor
@param1 kelimenin olup olmadigi kontrol edilen stack
@param2 stackte olup olmadigi kontrol edilen kelime
@return kelime varsa 1,yoksa 0
*/
int stackteVarMi(struct Stack* tmpStack,char* kelime){
     int i;
	 for (i = 0; i <= tmpStack->top; ++i) {
        if (!strcmp(tmpStack->items[i],kelime)) {
            return 1;
        }
    }
    return 0;
}



/*@brief Kullanilan kelimeleri kayit etmek icin
@param1 kayit edilen dosyada olup olmadigi kontrol edilen kelime
@return kelime varsa -1,yoksa 1*/
int addWordFile(char *kelime) {
    char dosya_kelime[MAX_SIZE];
    FILE *dosya = fopen("sozluk.txt", "a+"); // "a+" modunu kullanarak dosya sonuna ekleme 
    //dosya acilip acilmadigi kontrolu
    if (dosya == NULL) {
        printf("Dosya oluþturulamadý!");
        exit(1);
    } 
	else {
        fseek(dosya, 0, SEEK_SET); // Dosya imlecini dosyanýn baþýna getir
        while (fscanf(dosya, "%s", dosya_kelime) != EOF) {
            if (strcmp(kelime, dosya_kelime) == 0) {
                fclose(dosya);
                return -1; // Kelime bulundu
            }
        }
        fprintf(dosya, "%s\n", kelime);//kelimeyi dosyaya ekle
        fclose(dosya);
        return 1;
    }
}

//@brief Kullanilan kelimelerin tutuldugu dosyayi yazdirir kontrol amacli eklenmistir
void sozluk_goster() {
    char kelime[MAX_SIZE];
    FILE *dosya = fopen("sozluk.txt", "r");
    if (dosya == NULL) {
        printf("Dosya açýlamadý!");
        exit(1);
    }

    printf("Sözlük:\n");
    while (fscanf(dosya, "%s ", kelime) != EOF) {
        printf("%s\n", kelime);
    }

    fclose(dosya);
}

//@brief Kod bittiginde gidilen kelimeleri sifirlamak icin
void deleteFile() {
  FILE *dosya=fopen("sozluk.txt","w");
     if (dosya == NULL) {
        printf("File opening error.\n");
        return;
    }
    fclose(dosya);
}


/*@brief output.txt dosyasýndan kelimeleri okuyup kaynak kelime ile 
kaç harfinin farklý olduguna bakar eger 1 harf farkli ise daha once kullanilip kullanilmadigina bakar
eger bu kelime daha once kullanilmadiysa kelimenin gonderilen stacki kopyalar, kopyalanmis stacke kelimeyi ekler, daha sonra stacki queue yapisina enqueue eder
enqueue basarisizsa queuenin son halini yazdýrýr basarili ise bunu bildirir ve daha sonra i yi arttýrýr i kac tane stack eklendigini tutmak icin kullanilir
@param1 kelimelerin okunacagi dosya adi
@param2 ilk seferde kullanicinin girdigi kaynak kelime daha sonra queueden dequeue edilen stackin en ustundeki kelime
@param3 stacklerin eklenecegi queue
@param4 kelimelerin eklenecegi stack
@return dosya okuma basariliysa 0,dosya acmada sorun ciktiysa -1,kuyruk doluysa exit(1)*/
int readFile(char *dosya_adi,char* kaynakKelime,struct Queue *queue,struct Stack* mainStack){
	FILE *dosya = fopen(dosya_adi, "r");
	char kelime[MAX_SIZE];//dosyadan okunan kelime
    int i=0;//eklenen stack sayisini tutmak icin
    // Dosyanýn acilip acilmadigini kontrol et
    if (dosya == NULL) {
        printf("Dosya açýlýrken hata oluþtu");
        return -1;
    }
    //dosya sonuna gelene kadar kelime okur
     while (fscanf(dosya, "%s", kelime) != EOF){
        if (compareWords(kelime, kaynakKelime) == 1) //okunan keime ve kaynak kelime harf farki 1 mi kontolu
		{if(addWordFile(kelime)==1)//bu kelime daha once kullanildi mi kontrolu
		  {struct Stack* tmpStack = createStack();
        	tmpStack=copyStack(mainStack);
            pushStack(tmpStack,kelime);
			 if (!enqueue(queue, tmpStack))//queueya kelime eklendi mi kontrolu 
			 {
                //printQueue(queue);
                printf("Kuyruk dolu, %d. eleman eklenemedi.\n", i + 1);
                exit(1);
                free(tmpStack);
              }
		     else {
             printf("Stack %d kuyruga eklendi.\n", i + 1);
             //displayStack(tmpStack);
          }
			 i++; 
        
       }
    }
  }
    // Dosyayý kapat
    fclose(dosya);
    return 0;
}

/*@brief hedef kelimeye erisince veya queue bos olana kadar queueden stack dequeue etme islemi
@param1 dequeue islemi yapilacak queue
@param2 kullanicinin girdigi hedef kelime*/
void findShortestWay(struct Queue* queue,char* hedefKelime){
   struct Stack* tmpStack=createStack();//dequeue edilen stacki tutmak icin
   int flag=0;//whiledan cikis kontrolu icin
   //queue bos olana ya da kelime bulunana kadar dongu devam eder
   while(isEmptyQueue(queue)==0 && flag==0){
    tmpStack=dequeue(queue);//dequeue edilen stack tmpStacke atanir
    //hedef kelime ve dequeue edilen stackin en ustundeki kelime ayniysa
    if(compareWords(tmpStack->items[tmpStack->top], hedefKelime) == 0)
	{
    	printf("Kelime bulundu\n");
    	//printf("%s\n",tmpStack->items[tmpStack->top]);
    	printf("Kelime merdiveni:");
        displayStack(tmpStack);
        flag=1;//donguden cikmak icin
	}
	else
   readFile("output.txt",tmpStack->items[tmpStack->top],queue,tmpStack); //kelime bulunmadigi icin readFile'a dequeue edilen stackin en ustundeki kelime gonderilir islem devam eder
    //printQueue(queue); //her asamada queue yazdirilir
  }
  //whiledan neden cikildigi kontrolu
  if(flag==0){
  	printf("Kelime bulunamadi\n");
  }
}

/*@brief Kaynak kelime ve hedef kelimenin dictionary.txt de olup olmadigini kontol eder
@param1 kelimelerin yer aldýgý dosya ismi
@param2 kullanicinin girdigi dosyada olup olmadigi kontrol edilecek kelime
*/
void isInDict(char *dosya_adi,char* kelime){
	FILE *dosya = fopen(dosya_adi, "r");
	char sozlukKelime[MAX_SIZE]; //dosyadan okunan kelime
    int flag=0; //whiledan neden cikildigini kontrol etmek icin
    // Dosyanýn açýlýp açýlmadýðýný kontrol et
    if (dosya == NULL) {
        printf("Dosya açýlýrken hata oluþtu");
        return -1;
    }
    //dosya bitene kadar veya kelime bulunana kadar dongu devam eder
	while ((fscanf(dosya, "%s", sozlukKelime) != EOF)&&flag==0) {
       if(strcmp(sozlukKelime,kelime)==0){
       	  flag=1;//kelime bulundu
	   }
  }
   //whiledan neden cikildigi kontrolu
     if(flag==0){
     	printf("Kelime[%s]sozlukte yok!",kelime);
     	exit(1);
	 }
}

/*@brief Kaynak kelimenin uzunlugundaki kelimeleri dosyadan okur ve baska dosyaya kaydeder bu sekilde dosyadan okuma suresi azalacaktir
@param1 tum kelimelerin yer aldýgý dosya ismi
@param2 kaynak kelime uzunlugundaki kelimelerin yazilacagi dosya ismi
@param3 kaynak kelime uzunlugu
*/
void wordLengthToFile(const char *inputFileName, const char *outputFileName,int length) {
    FILE *inputFile, *outputFile;
    char word[LENGTH];

    // Okunacak dosyanýn adýný belirtin
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Girdi dosyasi acilamadi");
        return;
    }

    // Yazýlacak dosyanýn adýný belirtin
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Cikti dosyasi acilamadi");
        fclose(inputFile);
        return;
    }

    // Dosyadan kelimeleri okuyun, uzunluklarýna göre sýralayýn ve diðer dosyaya yazýn
    while (fscanf(inputFile, "%s", word) != EOF) {
        if(length==strlen(word))
        fprintf(outputFile, "%s\n", word);
    }

    // Dosyalarý kapatýn
    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
	struct Queue queue;
    initializeQueue(&queue);
    struct Stack* mainStack =createStack();
    int i;
    int length;//kelime uzunluðu
    char* kaynakKelime[LENGTH];
    char* hedefKelime[LENGTH];
    printf("Kaynak kelimeyi giriniz\n");
    scanf("%s",kaynakKelime);
    printf("Hedef kelimeyi giriniz\n");
    scanf("%s",hedefKelime);
    isInDict("dictionary.txt",kaynakKelime);
    isInDict("dictionary.txt",hedefKelime);
    length=strlen(kaynakKelime);
    if(length!=strlen(hedefKelime)){
    	printf("Harf sayilari esit olmali!\n");
    	return 0;
	}
	else if(!strcmp(kaynakKelime,hedefKelime)){
		printf("Kaynak kelime ve hedef kelime ayni\n");
		return 0;
	}
	else{
	addWordFile(kaynakKelime); 
    wordLengthToFile("dictionary.txt","output.txt",length);
    pushStack(mainStack,kaynakKelime);
    readFile("output.txt",kaynakKelime,&queue,mainStack);
    printQueue(&queue);
    findShortestWay(&queue,hedefKelime);
}
    deleteFile();
	return 0;
}


