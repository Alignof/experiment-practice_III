# 補足資料について

作業した際に記録する作業報告書の他に必要に応じて追加で補足資料を各実験ごとに追記する。  
具体的にはmarkdownで書いてPDFで出力し、他の作業報告書と合わせて提出することになる。  
理由としては、 

-   word上でプログラムを記載して説明するにはインデントやシンタックスハイライトの点でそぐわない面があるから
-   後から追記する際に作業報告書に上書きするのは作業記録として不適切だから

などが挙げられる  

大まかな流れとしては、
1. [Boost Note](https://boostnote.io/)を使用してmarkdown形式で資料を記述する
2. プレビュー機能を使い、外形を確認する
3. pandecを使い、latex経由でmarkdownをpdfに変換する

という流れだ。
変換するコマンドは以下。

```terminal
pandoc LED_SWITCH.md	-s -o output.pdf\
			--pdf-engine=lualatex\
			-V documentclass=ltjarticle\
			-V geometry:margin=1.5cm\
			-V geometry:a4paper\
			--highlight-style=breezedark
```

または、以下のサイトを使ってオンラインでmarkdownをpdfに変換する方法もある。  
> [https://md2pdf.netlify.com/](https://md2pdf.netlify.com/)

こちらは上記の方法と違って対応していない記法があったりせず便利。  

今回試して分かったがmarkdownをプレビューの形のままpdf化するのは困難でpdf形式にしてしまうと最大の利点である見た目の美しさが失われてしまうということが分かった。
  
markdownは方言が強く共有が難しいかもしれないが、きちんと使うツールを指定すればより簡単にわかりやすい報告書を作れるため全体の報告書の完成度が上がるだけでなくモダンなドキュメントを書く練習（githubではmarkdown形式でReadmeを書く）にもなるのではないかと今回使ってみて感じた。
