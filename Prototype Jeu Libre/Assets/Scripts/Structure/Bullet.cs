using UnityEngine;

public class BulletScript : MonoBehaviour
{
    [SerializeField] public float m_Speed = 10f;
    [SerializeField] public float m_Damage = 10f;
    [SerializeField] public GameObject m_pTarget = null;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }
    
    void FollowTarget()
    {
        Vector3 direction = (m_pTarget.transform.position - transform.position).normalized;
        transform.position += direction * m_Speed * Time.deltaTime;
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject == m_pTarget)
        {
            m_pTarget.GetComponent<Health>().TakeDamage(m_Damage);
            Destroy(gameObject);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (m_pTarget != null)
            FollowTarget();
        else
            Destroy(gameObject);
    }
}
