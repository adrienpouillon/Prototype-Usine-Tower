using UnityEngine;

public class Health : MonoBehaviour
{
    [SerializeField] public float m_MaxHealth = 10f;
    [SerializeField] public float m_Health;
    [SerializeField] public bool m_IsDead = false;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_Health = m_MaxHealth;
    }

    public void SetHealt(float health)
    {
        m_Health = health;
        m_MaxHealth = health;
        if (m_Health <= 0)
        {
            m_Health = 1;
            m_MaxHealth = 1;
        }
    }

    public void TakeDamage(float damage)
    {
        m_Health -= damage;
        if (m_Health <= 0)
        {
            m_IsDead = true;
        }
    }

    public bool IsDead()
    {
        return m_IsDead;
    }

    // Update is called once per frame
    void Update()
    {
        if(m_IsDead)
            Destroy(gameObject);
    }
}
