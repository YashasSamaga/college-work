from flask import render_template, request, session, abort

from config import category_config

from app.admin.forms import AddCategoryForm
from app.category.models import Category

from app import app
from app import db

@app.route('/admins', methods=['GET', 'POST'])
def admin_dashboard():
	return render_template('admin/dashboard.html')

@app.route('/admin/add_category', methods=['GET', 'POST'])
def admin_addcategory():
	if session.get('userid', -1) != 1:
		return abort(404)

	form = AddCategoryForm()

	if request.method == 'POST' and form.validate() == True:		
		category = Category(form.name.data, form.description.data, form.material_icon_id.data)
		db.session.add(category)
		db.session.commit()
		#form.default_project_cover.data.save(category_config['default_project_cover_url'].format(category.categoryid))

	return render_template('admin/add_category.html', form = form)
			
		
		
		
		
		
		
		
		
		
		
		
		
