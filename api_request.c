#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int post_score(int score_int)
{
  CURLcode ret;
  CURL *hnd;
  char score_str[4]; // 引数で受け取った整数型のscoreを文字列型に変換する為の変数.
  char post_data[10] = "score="; // post送信する際の変数.
  int data_size; // post送信する際に必要となるデータサイズを変数として宣言.

  sprintf(score_str, "%d", score_int); // 整数型のscoreを文字列型に変換.
  strcat(post_data, score_str); // post送信する為に文字列同士を結合. a.g.) "score=" + "10" -> "score=10"
  data_size = strlen(post_data); // post送信する際のデータの文字列をカウント.

  hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
  curl_easy_setopt(hnd, CURLOPT_URL, "http://0.0.0.0:8080/post_score"); // Post送信するURI, portによって変更する必要あり.
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, post_data); // Post送信で渡す際に指定するscore.
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)data_size);
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

  ret = curl_easy_perform(hnd);

  curl_easy_cleanup(hnd);
  hnd = NULL;

  return (int)ret;
}

int get_score()
{
  CURLcode ret;
  CURL *hnd;

  hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
  curl_easy_setopt(hnd, CURLOPT_URL, "http://0.0.0.0:8080/get_score"); // Post送信するURI, portによって変更する必要あり.
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

  ret = curl_easy_perform(hnd);

  curl_easy_cleanup(hnd);
  hnd = NULL;

  return (int)ret;

}

int main(int argc, char *argv[])
{
  int score = 1;

  printf("スコアの登録\n");
  post_score(score); // score登録

  printf("上位スコア、10件を取得\n");
  get_score(); // DBから上位10件のscoreのみを取得

  return 0;
}