from app.dbs import models

def get_pages( category_name ):
    category = models.Category.query.filter_by(name = category_name ).first()
    return category.pages.all()

def get_urls( category_name ):
    urls = []
    for page in get_pages( category_name ):
        urls.append(page.url)
    return urls

