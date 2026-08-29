from .dark_spellbook import dark_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    allowed = dark_spell_allowed_ingredients()
    for ing in allowed:
        if ing.lower() in ingredients.lower():
            return ("VALID")
    return ("INVALID")
