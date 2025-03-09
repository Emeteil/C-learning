from anicli_api_anigo_auth.anicli_api.source.animego import Profile, set_PHPSESSID
from dotenv import load_dotenv
import os

def main():
    load_dotenv()
    set_PHPSESSID(os.getenv("PHPSESSID"))
    
    pf = Profile()
    results = pf.get_planned_anime()
    
    for item in results:
        print(item.get_anime()
                  .get_json_info()
                  ["alternativeHeadline"]
                  [0])

if __name__ == "__main__":
    main()