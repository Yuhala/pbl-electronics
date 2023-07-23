from flask import Flask, render_template, request, session

app = Flask(__name__)
#app.config['SECRET_KEY'] = 'pi_secret_web_key'
#app.debug = True
#app.run(host='192.168.1.123', port=5000, debug=True, threaded=False) //use this line inside if(__main__)


@app.route('/')
def hello_pi():
    return 'Hello, I am a home automation Pi!'