Problem: Kelime merdiveni, verilen anlamlı bir kelimeden başlayıp, her adımda sadece tek bir harfin 
değiştirilmesiyle yine anlamlı kelimelerin elde edilmesi şeklinde ilerleyerek hedeflenen kelimeye 
ulaşılmasını sağlayan bir oyundur. Oyunun her aşamasında kelimenin harf sayısı değişmeden 
kalmalıdır. Aşağıda “stone” kelimesini “money” kelimesine taşıyan bir kelime merdiveni örneği 
verilmiştir.
stone → atone → alone → clone-→ clons → coons → conns → cones → coney → money
Kaynak kelimeden hedef kelimeye giden birden fazla kelime merdiveni olabilir. Örneğin, yukarıdaki 
stone→money örneği için bir başka kelime merdiveni;
stone → store → shore → chore → choke → choky → cooky → cooey → coney → money şeklindedir. 
Programınız en kısa kelime merdivenini bulmalıdır. Geçerli kelimeler için ödev ekinde verilen sözlük 
dosyası (dictionary.txt) kullanılacaktır.
Programınız, kullanıcıdan okunan kaynak ve hedef kelimeleri alarak en kısa merdiveni oluşturmalı ve 
adımlarını ekrana yazdırmalıdır. Problemin farklı çözüm yöntemleri bulunsa da ödevde kelime 
merdiveni problemini aşağıda anlatılan şekilde çözmeniz beklenmektedir. 
1. Kaynak kelime alınır ve sözlükte aynı uzunlukta olup tek bir harfi farklı olan tüm kelimeler 
bulunur. 
2. Her kelime için ayrı bir “stack” oluşturulur ve ilk önce kaynak kelime, sonra da tek harfi farklı 
kelime kendi stack’ine push edilir. 
3. Bu stack’lerin her biri bir queue’ya enqueue edilir. (Queue’da stack’ler saklanacaktır.)
4. Queue’dan bir eleman(stack) dequeue edilir, en üstteki kelimeye bakılır ve hedef kelimeye eşit 
olup olmadığı kontrol edilir. 
a. Eşitse, bu stack en kısa kelime merdiveninden oluşan çözümü içermektedir. 
b. Değilse, bu kelimeden tek harfi farklı ve aynı uzunluktaki tüm kelimeler sözlükten 
bulunur. Her yeni kelime için stack kopyalanır ve her kelime kendi stack’ine push edilir. 
Bu stackler queue’ya enqueue edilir.
5. Hedef kelimeye erişince veya queue boş olana kadar 4. adım tekrarlanır.


