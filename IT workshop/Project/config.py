WEBSITE_NAME = "FundMePlease"

jinja2_globals = {
	"WEBSITE_NAME" : WEBSITE_NAME
};

user_config = {
	"password_min_length" : 8,
	"password_max_length" : 32,
	"avatar_url" : "images/avatars/default{}.png"
};

category_config = {
	"default_project_cover_url" : "images/category/{}-project-default.jpg"
}

flask_config = {
	"SQLALCHEMY_DATABASE_URI" : "sqlite:///../database/main.db",
	"SQLALCHEMY_TRACK_MODIFICATIONS" : False,
	"SECRET_KEY" : "supersecureawesomeapp",
	"DEBUG" : True,
	"SECURITY_PASSWORD_SALT" : "absdef2341#12q1",
	
	"MAIL_SERVER" : 'smtp.gmail.com',
	"MAIL_PORT"	: 465,
	"MAIL_USE_SSL" : True,
	"MAIL_USERNAME" : 'yourmail@gmail.com',
	"MAIL_PASSWORD" : 'yourpassword',
	"MAIL_ASCII_ATTACHMENTS" : True
};
