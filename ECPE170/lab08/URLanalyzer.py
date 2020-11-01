import argparse
parser = argparse.ArgumentParser(description='URL analyzer that splits hostname and file name')
parser.add_argument('--url', 
                    action='store',
                    dest='url', 
                    required=True,
                    help='URL to split into host and file')

args=parser.parse_args()
url=args.url

#Add code here#
#sample execution: python3 myscript.py --url http://www.google.com/images/srpr/logo3w.png
#Output should look like:
#   Hostname is: www.google.com
#   The requested file is: /images/srpr/logo3w.png
splitto=url.split('//', 2)
splitto=url.split('/', 3)
hostname = splitto[2]
request = splitto[3]
print("Hostname is: "+hostname)
print("The requested file is: /"+request)
