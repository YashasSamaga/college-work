from app import db

class Category(db.Model):
	__tablename__ = "category"
	
	categoryid = db.Column(db.Integer, primary_key=True)
	name = db.Column(db.String(100), unique=True, nullable=False)
	description = db.Column(db.String(1000), nullable=False)
	material_icon_id = db.Column(db.String(64), nullable=False)
	def __init__(self, name, description, mii):
		self.name = name
		self.description = description
		self.material_icon_id = mii
