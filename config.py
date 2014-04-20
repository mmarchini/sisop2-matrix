from ConfigParser import ConfigParser

class Config(object):

    def __init__(self, filename="test_cases.cfg", sector="create"):
        self.config = ConfigParser()
        self.config.read(filename)
        self.sector = sector

    def get(self, option, default=None):
        value=None
        try:
            value = self.config.get(self.sector, option)
        except:
            return default
        if value:
            return eval(value)
        return value


